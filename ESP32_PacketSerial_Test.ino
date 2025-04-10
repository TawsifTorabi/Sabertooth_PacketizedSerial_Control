#include <Arduino.h>

// Sabertooth Driver ID Declaration
#define Sabertooth1 129  // Actuator Driver 1
#define Sabertooth2 135  // Actuator Driver 2

#define motor1_pin 25  // Pin for TX (both drivers share this pin)

// Create a Serial object for Sabertooth communication
HardwareSerial mySerial(1);

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);  

  // Start communication with Sabertooth drivers on Serial1 (TX pin D25)
  mySerial.begin(9600, SERIAL_8N1, -1, motor1_pin);  // Using HardwareSerial 1 with TX on D25

  // Initial message
  Serial.println("Starting Sabertooth Motor Test...");
  delay(2000);  // Wait for 2 seconds to prepare
}

void loop() {
  // Test motor 1 (on Sabertooth1) back and forth
  Serial.println("Testing Motor 1 (Sabertooth 1) Forward");
  drive(Sabertooth1, 1, 127);  // Forward direction
  delay(2000);  // Run for 2 seconds
  Serial.println("Testing Motor 1 (Sabertooth 1) Reverse");
  drive(Sabertooth1, 1, -127); // Reverse direction
  delay(2000);  // Run for 2 seconds

  // Test motor 2 (on Sabertooth1) back and forth
  Serial.println("Testing Motor 2 (Sabertooth 1) Forward");
  drive(Sabertooth1, 2, 127);  // Forward direction
  delay(2000);  // Run for 2 seconds
  Serial.println("Testing Motor 2 (Sabertooth 1) Reverse");
  drive(Sabertooth1, 2, -127); // Reverse direction
  delay(2000);  // Run for 2 seconds

  // Test motor 3 (on Sabertooth2) back and forth
  Serial.println("Testing Motor 3 (Sabertooth 2) Forward");
  drive(Sabertooth2, 1, 127);  // Forward direction
  delay(2000);  // Run for 2 seconds
  Serial.println("Testing Motor 3 (Sabertooth 2) Reverse");
  drive(Sabertooth2, 1, -127); // Reverse direction
  delay(2000);  // Run for 2 seconds

  // Test motor 4 (on Sabertooth2) back and forth
  Serial.println("Testing Motor 4 (Sabertooth 2) Forward");
  drive(Sabertooth2, 2, 127);  // Forward direction
  delay(2000);  // Run for 2 seconds
  Serial.println("Testing Motor 4 (Sabertooth 2) Reverse");
  drive(Sabertooth2, 2, -127); // Reverse direction
  delay(2000);  // Run for 2 seconds

  // After the test, stop all motors
  Serial.println("Stopping all motors...");
  stop(Sabertooth1, 1);
  stop(Sabertooth1, 2);
  stop(Sabertooth2, 1);
  stop(Sabertooth2, 2);
  delay(5000);  // Wait for 5 seconds before repeating the test
}

// Sabertooth Drive Command Utility Function
void stcommand(byte address, int speed, byte motor) {
  byte checksum = (address + motor + speed) & B01111111;  // Calculate the checksum
  mySerial.write(address);                                // Send the motor controller address
  mySerial.write(motor);                                  // Send the motor number (0 or 1 for Sabertooth)
  mySerial.write(speed);                                  // Send the speed value (-127 to 127)
  mySerial.write(checksum);                               // Send the checksum byte
}

// Sabertooth Control Function
void drive(int address, int motorNo, int speed) {
  if ((motorNo == 1 || motorNo == 2) && (speed >= -127 && speed <= 127)) {
    if (motorNo == 1 && speed < 0) {
      stcommand(address, -speed, 1);  // Motor 1 reverse
    } else if (motorNo == 1 && speed > 0) {
      stcommand(address, speed, 0);   // Motor 1 forward
    } else if (motorNo == 1 && speed == 0) {
      stcommand(address, 0, 0);       // Motor 1 stop
    } else if (motorNo == 2 && speed > 0) {
      stcommand(address, speed, 4);   // Motor 2 forward
    } else if (motorNo == 2 && speed < 0) {
      stcommand(address, -speed, 5);  // Motor 2 reverse
    } else if (motorNo == 2 && speed == 0) {
      stcommand(address, 0, 4);       // Motor 2 stop
    }
  }
}

// Stop Motor Command
void stop(byte address, int motorNo) {
  if (motorNo == 1) {
    stcommand(address, 0, 0);  // Stop motor 1
  } else if (motorNo == 2) {
    stcommand(address, 0, 4);  // Stop motor 2
  }
}
