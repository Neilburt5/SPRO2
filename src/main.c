#include <avr/io.h>
#include <util/delay.h>

// Motor 1
#define motor1StepPin 0
#define motor1DirPin 2
#define motor1EnPin 8

// Motor 2
#define motor2StepPin 1
#define motor2DirPin 3
#define motor2EnPin 9

// Motor 3
#define motor3StepPin 4
#define motor3DirPin 5
#define motor3EnPin 10

// Color thresholds
const int redMin = 19;
const int redMax = 194;
const int greenMin = 18;
const int greenMax = 235;
const int blueMin = 23;
const int blueMax = 187;

// Function to check if a color is within the specified range
int isColorInRange(int value, int minRange, int maxRange) {
  return (value >= minRange && value <= maxRange) ? 1 : 0;
}

// Function to configure TCS3200 color sensor
void configureColorSensor() {
  // Configure sensor pins as input
  DDRC &= ~(1 << PC0); // S0
  DDRC &= ~(1 << PC1); // S1
  DDRC &= ~(1 << PC2); // OUT

  // Set S0 and S1 to select scaling factor 1:1
  PORTC &= ~(1 << PC0); // S0 LOW
  PORTC &= ~(1 << PC1); // S1 LOW
}

// Function to read analog values from the ADC
int analogRead(int channel) {
  // Configure ADC
  ADMUX = (1 << REFS0) | (channel & 0x0F); // Set reference voltage to AVCC and select ADC channel
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC and set ADC prescaler to 128

  // Start conversion
  ADCSRA |= (1 << ADSC);

  // Wait for conversion to complete
  while (ADCSRA & (1 << ADSC));

  // Return converted value
  return ADC;
}

// Function to read color values from TCS3200 color sensor
void readColorSensor(int* red, int* green, int* blue) {
  // Set S2 and S3 to select red filter
  PORTC &= ~(1 << PC2); // OUT LOW
  PORTC &= ~(1 << PC1); // S1 LOW
  PORTC |= (1 << PC0);  // S0 HIGH

  // Wait for the sensor to stabilize
  _delay_ms(10);

  // Read red value
  *red = analogRead(PC2);

  // Set S2 and S3 to select green filter
  PORTC &= ~(1 << PC2); // OUT LOW
  PORTC |= (1 << PC1);  // S1 HIGH
  PORTC &= ~(1 << PC0); // S0 LOW

  // Wait for the sensor to stabilize
  _delay_ms(10);

  // Read green value
  *green = analogRead(PC2);

  // Set S2 and S3 to select blue filter
  PORTC |= (1 << PC2);  // OUT HIGH
  PORTC &= ~(1 << PC1); // S1 LOW
  PORTC |= (1 << PC0);  // S0 HIGH

  // Wait for the sensor to stabilize
  _delay_ms(10);

  // Read blue value
  *blue = analogRead(PC2);
}

int main(void) {
  // Motor 1
  DDRD |= (1 << motor1DirPin) | (1 << motor1StepPin); // Set motor1DirPin and motor1StepPin as output
  DDRB |= (1 << PB0); // Set motor1EnPin as output
  PORTB &= ~(1 << PB0); // Set motor1EnPin LOW to enable the driver

  // Motor 2
  DDRD |= (1 << motor2DirPin) | (1 << motor2StepPin); // Set motor2DirPin and motor2StepPin as output
  DDRB |= (1 << PB1); // Set motor2EnPin as output
  PORTB &= ~(1 << PB1); // Set motor2EnPin LOW to enable the driver

  // Motor 3
  DDRD |= (1 << motor3DirPin) | (1 << motor3StepPin); // Set motor3DirPin and motor3StepPin as output
  DDRB |= (1 << PB2); // Set motor3EnPin as output
  PORTB &= ~(1 << PB2); // Set motor3EnPin LOW to enable the driver

  // Color sensor variables
  int redValue, greenValue, blueValue;

  // Configure color sensor
  configureColorSensor();

  while (1) {
    // Read color sensor values and store them in variables: redValue, greenValue, blueValue
    readColorSensor(&redValue, &greenValue, &blueValue);

    // Determine direction based on color
    int clockwise = 0;
    if (isColorInRange(redValue, redMin, redMax) &&
        isColorInRange(greenValue, greenMin, greenMax) &&
        isColorInRange(blueValue, blueMin, blueMax)) {
      clockwise = 1; // Move clockwise if color is within the specified ranges
    }

    // Move Motor 1
    PORTD |= (1 << motor1DirPin); // Set motor1DirPin HIGH to move in a particular direction
    for (int x = 0; x < 800; x++) {
      PORTD |= (1 << motor1StepPin); // Set motor1StepPin HIGH
      _delay_us(100);
      PORTD &= ~(1 << motor1StepPin); // Set motor1StepPin LOW
      _delay_us(100);
    }
    _delay_ms(100); // One second delay

    // Move Motor 2
    PORTD |= (1 << motor2DirPin); // Set motor2DirPin HIGH to move in a particular direction
    for (int x = 0; x < 800; x++) {
      PORTD |= (1 << motor2StepPin); // Set motor2StepPin HIGH
      _delay_us(100);
      PORTD &= ~(1 << motor2StepPin); // Set motor2StepPin LOW
      _delay_us(100);
    }
    _delay_ms(100); // One second delay

    // Move Motor 3
    PORTD |= (1 << motor3DirPin); // Set motor3DirPin HIGH to move in a particular direction
    for (int x = 0; x < 800; x++) {
      PORTD |= (1 << motor3StepPin); // Set motor3StepPin HIGH
      _delay_us(100);
      PORTD &= ~(1 << motor3StepPin); // Set motor3StepPin LOW
      _delay_us(100);
    }
    _delay_ms(100); // One second delay
  }

  return 0;
}