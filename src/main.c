// Automatic Room Lighting System using ATmega32
// Detects human entry/exit using IR sensors and controls room lighting

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// === Pin Definitions ===
#define SENSOR_IN   PINC
#define SENSOR1     PC0    // IR Sensor 1 (outside)
#define SENSOR2     PC1    // IR Sensor 2 (inside)
#define RELAY_PIN   PD0    // Output pin to relay module
#define SEGMENT_PORT PORTB // 7-segment output
#define SEGMENT_DDR  DDRB

// === 7-Segment Display Digits (Common Cathode) ===
uint8_t digits[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

volatile uint8_t people_count = 0;

// Display visitor count on 7-segment display
void display_count(uint8_t count) {
    if (count <= 9) {
        SEGMENT_PORT = digits[count];
    } else {
        SEGMENT_PORT = 0xFF; // Overflow indicator
    }
}

int main(void) {
    // === Initialize IO Pins ===
    DDRC &= ~((1 << SENSOR1) | (1 << SENSOR2));      // Input: IR Sensors
    PORTC |= (1 << SENSOR1) | (1 << SENSOR2);        // Enable pull-ups

    DDRD |= (1 << RELAY_PIN);                        // Output: Relay control
    SEGMENT_DDR = 0xFF;                              // Output: 7-segment
    SEGMENT_PORT = 0x00;

    uint8_t sensor1_last = 1, sensor2_last = 1;

    while (1) {
        uint8_t s1 = (SENSOR_IN & (1 << SENSOR1)) == 0;
        uint8_t s2 = (SENSOR_IN & (1 << SENSOR2)) == 0;

        // Entry: Sensor1 triggers first, then Sensor2
        if (s1 && !sensor1_last) {
            _delay_ms(50);
            if ((SENSOR_IN & (1 << SENSOR2)) == 0) {
                people_count++;
                if (people_count > 0)
                    PORTD |= (1 << RELAY_PIN); // Turn ON relay
                display_count(people_count);
                _delay_ms(500);
            }
        }

        // Exit: Sensor2 triggers first, then Sensor1
        if (s2 && !sensor2_last) {
            _delay_ms(50);
            if ((SENSOR_IN & (1 << SENSOR1)) == 0) {
                if (people_count > 0)
                    people_count--;
                if (people_count == 0)
                    PORTD &= ~(1 << RELAY_PIN); // Turn OFF relay
                display_count(people_count);
                _delay_ms(500);
            }
        }

        // Update last state
        sensor1_last = !((SENSOR_IN & (1 << SENSOR1)) == 0);
        sensor2_last = !((SENSOR_IN & (1 << SENSOR2)) == 0);
    }
}
