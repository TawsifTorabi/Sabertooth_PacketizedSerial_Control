# Sabertooth Motor Driver Packetized Serial Control (AVR and ESP)

This project demonstrates how to communicate with **two Sabertooth motor drivers** using a single **TX pin (D25)** on an ESP32 microcontroller. Each driver controls **two motors**, for a total of **four independently controlled motors**.

## Features

- Communicates via **Serial1** using the Sabertooth simplified serial protocol.
- Drives each motor (forward and reverse) for 2 seconds.
- Stops all motors after one cycle.
- Uses **Sabertooth packetized serial mode** (with address and checksum).
- Designed for ESP32 using **HardwareSerial**.

## Wiring

- **TX pin (GPIO 25)** → Connect to the **S1 (signal)** pin on both Sabertooth motor drivers.
- **GND** → Common ground with both drivers.
- Ensure both Sabertooth drivers are set to **packetized serial mode** and configured with the correct addresses:
  - `Sabertooth1`: Address **129**
  - `Sabertooth2`: Address **135**

> ⚠️ Note: You must configure the DIP switches on the Sabertooth accordingly to match these addresses.

Check the PDF at page 18 for DIP Switch configurations. - [Sabertooth 2x25 Motor Driver Manual](https://www.dimensionengineering.com/datasheets/Sabertooth2x25v2.pdf)


## Motor Mapping

| Driver       | Motor Number | Actual Motor |
|--------------|--------------|----------------|
| Sabertooth1  | 1            | Motor 1       |
| Sabertooth1  | 2            | Motor 2       |
| Sabertooth2  | 1            | Motor 3       |
| Sabertooth2  | 2            | Motor 4       |

## Usage

1. Flash the code to your ESP32 using the Arduino IDE.
2. Open the **Serial Monitor** at `115200 baud` to view debug output.
3. Observe each motor running forward and reverse in sequence.
4. All motors stop after the test, and the cycle repeats after a 5-second delay.

## Code Overview

### Functions

- `drive(address, motorNo, speed)`
  - Controls direction and speed.
  - `speed`: Range from -127 (reverse) to 127 (forward), `0` to stop.
- `stop(address, motorNo)`
  - Stops the specified motor.
- `stcommand(address, speed, motor)`
  - Sends the actual packet to the motor driver.

## Dependencies

- No external libraries required.
- Uses built-in `HardwareSerial`.

## License

This code is open-source and provided as-is, without warranty. You are free to modify and use it for your own projects.
