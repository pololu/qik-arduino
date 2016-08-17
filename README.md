# Arduino library for the Pololu qik dual serial motor controllers

Version: 2.0.0<br>
Release date: 2016-08-16<br>
[![Build Status](https://travis-ci.org/pololu/qik-arduino.svg?branch=master)](https://travis-ci.org/pololu/qik-arduino)<br>
[www.pololu.com](https://www.pololu.com/)

## Summary

This is a library for an
[Arduino-compatible controller](https://www.pololu.com/arduino) that
interfaces with the
[Pololu qik dual serial motor controllers](https://www.pololu.com/category/97/pololu-qik-dual-serial-motor-controllers).
It makes it easy to control two brushed DC motors with a simple serial
interface.

## Getting Started

### Hardware

The
[qik controllers](https://www.pololu.com/category/97/pololu-qik-dual-serial-motor-controllers)
can be purchased on Pololu's website.  Before continuing, careful
reading of the product page as well as the user's guide
([2s9v1](https://www.pololu.com/docs/0J25) or
[2s12v10](https://www.pololu.com/docs/0J29)) is recommened.

The example programs require the appropriate set of connections to be
made with wires between the Arduino and the qik:

#### qik 2s9v1

    Arduino       - qik 2s9v1
    --------------------------
    5V            - VCC
    GND           - GND
    Digital Pin 2 - TX
    Digital Pin 3 - RX
    Digital Pin 4 - RESET

#### qik 2s12v10


    Arduino       - qik 2s12v10
    --------------------------
    GND           - GND
    Digital Pin 2 - TX
    Digital Pin 3 - RX
    Digital Pin 4 - RESET

**Do not** connect the 5V output on the Arduino to the 5V output on the qik 2s12v10!

**Note:** If you are using an Arduino variant that does not use an
ATmega328P or ATmega168 (such as a Mega or Leonardo), the default pin
assignments will not work for you and will need to be changed. Please
see the Arduino
[SoftwareSerial Library reference](https://arduino.cc/en/Reference/SoftwareSerial)
for more information.


### Software

If you are using version 1.6.2 or later of the
[Arduino software (IDE)](https://www.arduino.cc/en/Main/Software), you can use
the Library Manager to install this library:

1. In the Arduino IDE, open the "Sketch" menu, select "Include Library", then
   "Manage Libraries...".
2. Search for "PololuQik".
3. Click the PololuQik entry in the list.
4. Click "Install".

If this does not work, you can manually install the library:

1. Download the
   [latest release archive from GitHub](https://github.com/pololu/qik-arduino/releases)
   and decompress it.
2. Rename the folder "qik-arduino-xxxx" to "PololuQik".
3. Drag the "PololuQik" folder into the "libraries" directory inside your
   Arduino sketchbook directory. You can view your sketchbook location by
   opening the "File" menu and selecting "Preferences" in the Arduino IDE. If
   there is not already a "libraries" folder in that location, you should make
   the folder yourself.
4. After installing the library, restart the Arduino IDE.

## Examples

Several example sketches are available that show how to use the
library. You can access them from the Arduino IDE by opening the
"File" menu, selecting "Examples", and then selecting "PololuQik". If
you cannot find these examples, the library was probably installed
incorrectly and you should retry the installation instructions above.

### Qik2s9v1Demo and Qik2s12v10Demo

Each of these programs ramps motor 1 from stopped to full speed
forward, ramps down to full speed reverse, and back to stopped.  Then,
it does the same with the other motor.  For the qik 2s12v10, both
motors' current readings are sent over serial and can be seen with the
serial monitor.

### Qik2s9v1Config and Qik2s12v10Config

Each of these programs reads and displays the configuration parameters
of the qik.  They can also be used to change the configuration
parameters by uncommenting and editing the appropriate calls to
`setConfigShowResult()`.

The configuration parameters are stored in non-volatile memory that is
rated for a limited number of erase/write cycles, so they are not
intended to be written frequently.  (Once set, these parameters will
retain their values even if the qik is powered off.)  If you need to
change the parameters, we recommend that you run the configuration
program once to set them and then load your final program on your
Arduino, which should assume that the parameters have already been set
correctly.  See the comments at the top of the configuration programs
and the user's guides for more details.

## Documentation

This library defines a `PololuQik` base class that implements commands
common to both versions of the qik.  Two derived classes,
`PololuQik2s9v1` and `PololuQik2s12v10`, handle commands specific to
each version.

The `PololuQik` class is itself derived from the `SoftwareSerial` class,
so you can use `SoftwareSerial` member functions (like `write()` and
`listen()`) for direct access to the serial interface used to
communicate with the qik.

The library does not implement any serial communication timeouts, so
your sketch will hang if the qik is not connected properly or does not
respond as expected.  It uses the compact protocol, not the Pololu
protocol, so it cannot be used to control multiple qiks daisy-chained
together on the same serial line.

### Library Reference

#### PololuQik

- `PololuQik(unsigned char receivePin, unsigned char transmitPin,
  unsigned char resetPin)` <br> Constructor; sets pins as specified.
  The receive and transmit pins are specified from the perspective of
  the **Arduino** (so the receive pin should be connected to the TX
  pin on the qik and the transmit pin should be connected to the RX
  pin on the qik).
- `void init(long speed = 9600)` <br> Resets the qik and initializes
   serial communication with it at the specified baud rate (defaults
   to 9600 bps if unspecified).
- `char getFirmwareVersion()` <br> Returns an ASCII byte that
  represents the version of the firmware running on the qik.
- `byte getErrors()` <br> Returns a byte that indicates any errors
  that have been detected since the errors were last read.  See the
  user's guides for the meaning of each bit.
- `byte getConfigurationParameter(byte parameter)` <br> Returns the
  current value of the specified configuration parameter.
- `byte setConfigurationParameter(byte parameter, byte value)` <br> Sets
  the specified configuration parameter to the specified value.

- `void setM0Speed(int speed)` <br> Sets speed and direction for motor
  M0. `speed` should be between -127 and 127 in 7-bit mode or -255 and
  255 in 8-bit mode.  Positive values correspond to motor current
  flowing from the + pin to the - pin. Negative values correspond to
  motor current flowing from the - pin to the + pin.
- `void setM1Speed(int speed)` <br> Sets speed and direction for motor
  M1.
- `void setSpeeds(int m0Speed, int m1Speed)` <br> Sets speed and
  direction for both motors.

#### PololuQik2s9v1

- `void setM0Coast()` <br> Sets motor M0 to coast.
- `void setM1Coast()` <br> Sets motor M1 to coast.
- `void setCoasts()` <br> Sets both motors to coast.

#### PololuQik2s12v10

- `void setM0Brake(unsigned char brake)` <br> Sets brake for motor
  M0. `brake` should be between 0 and 127. 0 corresponds to full
  coast, and 127 corresponds to full brake.
- `void setM1Brake(unsigned char brake)` <br> Sets brake for motor
  M1.
- `void setBrakes(unsigned char m0Brake, unsigned char m1Brake)` <br>
  Sets brake for both motors.
- `unsigned char getM0Current()` <br> Returns raw current reading from
  motor M0.
- `unsigned char getM1Current()` <br> Returns raw current reading from
  motor M1.
- `unsigned int getM0CurrentMilliamps()` <br> Returns current reading
  from motor M0 in milliamps.
- `unsigned int getM1CurrentMilliamps()` <br> Returns current reading
  from motor M1 in milliamps.
- `unsigned char getM0Speed()` <br> Returns the present target motor
  speed for motor M0.
- `unsigned char getM1Speed()` <br> Returns the present target motor
  speed for motor M1.

## Version history
* 2.0.0 (2016-08-16): Updated library to work with the Arduino Library Manager.
* 1.1.1 (2016-06-08): Made SoftwareSerial include to be a system header include (thanks Dippyskoodlez).
* 1.1.0 (2013-05-22): Added calls to `SoftwareSerial::listen()` for better behavior when using multiple `PololuQik` instances.
* 1.0.0 (2012-05-07): Original release.
