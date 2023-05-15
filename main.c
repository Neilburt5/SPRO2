#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Stepper.h"


// Define color sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Calibration Values
// Get these from Calibration Sketch
int redMin = 19; // Red minimum value
int redMax = 194; // Red maximum value
int greenMin = 18; // Green minimum value
int greenMax = 235; // Green maximum value
int blueMin = 23; // Blue minimum value
int blueMax = 187; // Blue maximum value

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values
int redValue;
int greenValue;
int blueValue;

// Function prototypes
int getRedPW();
int getGreenPW();
int getBluePW();    


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


    // Set S0 - S3 as outputs
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    // Set Sensor output as input
    pinMode(sensorOut, INPUT);


    // Set Frequency scaling to 20%
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);

    // Setup Serial Monitor
    printf("Starting color sensor calibration and measurement\n");

    // Calibration loop, still left to add Libraries and LCD_code to show it in the monitor
    printf("Calibrating...\n");
    for (int i = 0; i < 10; i++) {
        // Read Red value
        redPW = getRedPW();
        if (redPW < redMin) {
            redMin = redPW;
        }
        if (redPW > redMax) {
            redMax = redPW;
        }
        delay(100);

return 0;
}
    }
