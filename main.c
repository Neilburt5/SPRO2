#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "i2cmaster.h"
#include "lcd.h"
#include "lm75.h"

int main (void){
    
    uart_init(); // Open the communication with the microcontroller
    io_redirect(); // Redirect input and output to the communication

    //Steps to enable the LCD
    i2c_init(); //Initialize the i2c communication
    LCD_init(); //Initialize the LCD
    lm75_init(); //Initialize the temperature sensor

    //Configuration of the LEDs
    DDRD = 0xFF; //I/O board: PD4...7 as outputs, for LEDs
    PORTD = 0X00; //Set output LEDs to off

    //Configuration of the input buttons
    DDRC = 0xF0; // I/O board PC0...3 as inputs, for buttons
    PORTC = 0x3F; //Enable internal pull at PC0...3 inputs

    


return 0;
}

