#include <avr/io.h>
#include <util/delay.h>

#define stepPin 5
#define dirPin 2
#define enPin 8

int main(void)
{
    DDRD |= (1 << DDD2) | (1 << DDD5); // Set dirPin and stepPin as output
    DDRB |= (1 << DDB0); // Set enPin as output
    PORTB &= ~(1 << PORTB0); // Set enPin LOW to enable the driver

    while (1) {
        PORTD |= (1 << PORTD2); // Set dirPin HIGH to move in a particular direction
        for (int x = 0; x < 800; x++) {
            PORTD |= (1 << PORTD5); // Set stepPin HIGH
            _delay_us(100);
            PORTD &= ~(1 << PORTD5); // Set stepPin LOW
            _delay_us(100);
        }
        _delay_ms(100); // One second delay
        PORTD &= ~(1 << PORTD2); // Set dirPin LOW to change direction of rotation
        for (int x = 0; x < 800; x++) {
            PORTD |= (1 << PORTD5); // Set stepPin HIGH
            _delay_us(100);
            PORTD &= ~(1 << PORTD5); // Set stepPin LOW
            _delay_us(100);
        }
        _delay_ms(100);
    }
    return 0;
}