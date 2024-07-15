#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 400

// create an instance of the stepper class for motor 1
Stepper stepper1(STEPS, 4, 5, 6, 7);
Stepper stepper2(STEPS, 8, 9, 10, 11); // potential bug here: now the stepper2 only has 200 STEPS. need to change it if going to use it

// Variables to keep track of the last step time for motor 1
unsigned long lastStepTime1 = 0;

// Variables for motor 1 speed control
float desiredRPM1 = 0.2; // Initial RPM for Motor 1
float minRPM = 0.001; // Minimum RPM
float maxRPM = 0.3; // Maximum RPM

void setup()
{
  Serial.begin(9600);
  Serial.println("Stepper test!");

  // Print the initial desired RPM for debugging
  Serial.print("Initial Desired RPM for Motor 1: ");
  Serial.println(desiredRPM1);
}

void loop()
{
  unsigned long currentTime = millis();

  // Read analog value from pin 12
  int analogValue = analogRead(A0);

  // Map analog value to desired RPM range
  desiredRPM1 = map(analogValue, 0, 1023, minRPM * 1000, maxRPM * 1000) / 1000.0;

  // Calculate step delay for motor 1
  float stepDelay1 = (60.0 * 1000.0) / (STEPS * desiredRPM1);

  // Print the current desired RPM and step delay for debugging
  Serial.print("Motor 1 RPM: ");
  Serial.println(desiredRPM1);
  // Serial.print("  Motor 1 RPM: ");
  // Serial.println(analogValue);

  // Control Motor 1
  if (currentTime - lastStepTime1 >= stepDelay1) {
    stepper1.step(1);
    lastStepTime1 = currentTime;
  }
  
  // Optional delay to observe changes in speed
  // delay(1000);
}