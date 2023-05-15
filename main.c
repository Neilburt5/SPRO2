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

// Variables for steppedmotor
const int stepsPerRevolution = 200;
const int numCilindros = 8;
const int stepPin1 = 2; const int dirPin1 = 3;
const int stepPin2 = 4; const int dirPin2 = 5;
const int stepPin3 = 6; const int dirPin3 = 7;
const int stepPin4 = 8; const int dirPin4 = 9;

//Inicialize the steppermotors
Stepper motor1(stepsPerRevolution, stepPin1, dirPin1);
Stepper motor2(stepsPerRevolution, stepPin2, dirPin2);
Stepper motor3(stepsPerRevolution, stepPin3, dirPin3);
Stepper motor4(stepsPerRevolution, stepPin4, dirPin4);

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

// Function for moving the motors
void moverCilindros(int distancia) {

// Calculate the number of steps for the neccesary distance
int pasos = distancia * 200 / 5;

// Movemos los motores
motor1.setSpeed(100);motor1.step(pasos);
motor2.setSpeed(100);motor2.step(-pasos);
motor3.setSpeed(100);motor3.step(pasos);
motor4.setSpeed(100);motor4.step(-pasos);
}
