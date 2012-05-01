#include "PololuQik.h"

PololuQik::PololuQik(uint8_t receivePin, uint8_t transmitPin, uint8_t resetPin) : _serial(receivePin, transmitPin)
{
  _resetPin = resetPin;
}

void PololuQik::init()
{
  // reset the qik
  digitalWrite(_resetPin, LOW);
  pinMode(_resetPin, OUTPUT); // drive low
  delay(1);
  pinMode(_resetPin, INPUT); // return to high-impedance input (reset is internally pulled up on qik)
  delay(1);

  // set baud rate
  _serial.write(0xAA);
}

void PololuQik::setM0Speed(int16_t speed)
{
  uint8_t cmd[2];
  uint8_t reverse = 0;

  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1; // preserve the direction
  }

  if (speed > 255)
    speed = 255;

  if (speed > 127)
  {
    cmd[0] = reverse ? 0x8B : 0x89; // these commands set speed to (128 + speed) in 8-bit mode
    cmd[1] = speed - 128;
  }
  else
  {
    cmd[0] = reverse ? 0x8A : 0x88;
    cmd[1] = speed;
  }

  _serial.write(cmd, 2);
}

void PololuQik::setM1Speed(int16_t speed)
{
  uint8_t cmd[2];
  uint8_t reverse = 0;

  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1; // preserve the direction
  }

  if (speed > 255)
    speed = 255;

  if (speed > 127)
  {
    cmd[0] = reverse ? 0x8F : 0x8D; // these commands set speed to (128 + speed) in 8-bit mode
    cmd[1] = speed - 128;
  }
  else
  {
    cmd[0] = reverse ? 0x8E : 0x8C;
    cmd[1] = speed;
  }

  _serial.write(cmd, 2);
}

void PololuQik::setSpeeds(int16_t m0Speed, int16_t m1Speed)
{
  setM0Speed(m0Speed);
  setM1Speed(m1Speed);
}

uint8_t PololuQik::getErrors()
{
	_serial.write(0x82);
	return _serial.read();
}