#include <stdio.h>
//#include <wiringPi.h>

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

void setup() {
  // Set up WiringPi
  wiringPiSetup();

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
  printf("Red = %d - Green = %d - Blue = %d\n", redValue, greenValue, blueValue);
}

int getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Define integer to represent Pulse Width
  int PW;

  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);

  // Return the value
  return PW;
}

int getGreenPW() {
  // Set sensor to read Green only
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Define integer to represent Pulse Width
  int PW;

  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);

  // Return the value
  return PW;
}

int getBluePW() {
  // Set sensor to read Blue only
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Define integer to represent Pulse Width
  int PW;

  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);

  // Return the value
  return PW;
}

int main() {
  // Call the setup function
  setup();

  while (1) {
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

  return 0;
}
