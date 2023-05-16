#define F_CPU 16000000UL
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Stepper.h"

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

//Variables for color sensor
/*Variable from calibration*/
int redMin = 19; // Red minimum value
int redMax = 194; // Red maximum value
int greenMin = 18; // Green minimum value
int greenMax = 235; // Green maximum value
int blueMin = 23; // Blue minimum value
int blueMax = 187; // Blue maximum value

/*Variables for Color Pulse Width*/
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
/*Final color value*/
int redValue;
int greenValue;
int blueValue;

//Inicialize the steppermotors
Stepper motor1(stepsPerRevolution, stepPin1, dirPin1);
Stepper motor2(stepsPerRevolution, stepPin2, dirPin2);
Stepper motor3(stepsPerRevolution, stepPin3, dirPin3);
Stepper motor4(stepsPerRevolution, stepPin4, dirPin4);

//Initialize the color sensor
void setup() {


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
    Serial.begin(9600);}

// Declare color sensor functions
void loop() {

    // Read Red value
    redPW = getRedPW();
    // Map to value from 0-255
    redValue = map(redPW, redMin, redMax, 255, 0);
    // Delay to stabilize sensor
    delay(200);

    // Read Green value
    greenPW = getGreenPW();
    // Map to value from 0-255
    greenValue = map(greenPW, greenMin, greenMax, 255, 0);
    // Delay to stabilize sensor
    delay(200);

    // Read Blue value
    bluePW = getBluePW();
    // Map to value from 0-255
    blueValue = map(bluePW, blueMin, blueMax, 255, 0);
    // Delay to stabilize sensor
    delay(200);

    // Print output to Serial Monitor
    printf("Red = %d - Green = %d - Blue = %d\n", redValue, greenValue, blueValue);
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

int main (void){

}

