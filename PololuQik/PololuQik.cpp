#include "PololuQik.h"

uint8_t cmd[5]; // serial command buffer

PololuQik::PololuQik(uint8_t receivePin, uint8_t transmitPin, uint8_t resetPin) : SoftwareSerial(receivePin, transmitPin)
{
  _resetPin = resetPin;
}

void PololuQik::init(long speed /* = 9600 */)
{
  // reset the qik
  digitalWrite(_resetPin, LOW);
  pinMode(_resetPin, OUTPUT); // drive low
  delay(1);
  pinMode(_resetPin, INPUT); // return to high-impedance input (reset is internally pulled up on qik)
  delay(10);

  begin(speed);
  write(0xAA); // allow qik to autodetect baud rate
}

uint8_t PololuQik::getFirmwareVersion()
{
  write(QIK_GET_FIRMWARE_VERSION);
  while (available() < 1);
  return read();
}

uint8_t PololuQik::getErrors()
{
  write(QIK_GET_ERROR_BYTE);
  while (available() < 1);
  return read();
}

uint8_t PololuQik::getConfigurationParameter(uint8_t parameter)
{
  cmd[0] = QIK_GET_CONFIGURATION_PARAMETER;
  cmd[1] = parameter;
  write(cmd, 2);
  while (available() < 1);
  return read();
}

uint8_t PololuQik::setConfigurationParameter(uint8_t parameter, uint8_t value)
{
  cmd[0] = QIK_SET_CONFIGURATION_PARAMETER;
  cmd[1] = parameter;
  cmd[2] = value;
  cmd[3] = 0x55;
  cmd[4] = 0x2A;
  write(cmd, 5);
  while (available() < 1);
  return read();
}

void PololuQik::setM0Speed(int16_t speed)
{
  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1; // preserve the direction
  }

  if (speed > 255)
    speed = 255;

  if (speed > 127)
  {
    // 8-bit mode: actual speed is (speed + 128)
    cmd[0] = reverse ? QIK_MOTOR_M0_REVERSE_8_BIT : QIK_MOTOR_M0_FORWARD_8_BIT;
    cmd[1] = speed - 128;
  }
  else
  {
    cmd[0] = reverse ? QIK_MOTOR_M0_REVERSE : QIK_MOTOR_M0_FORWARD;
    cmd[1] = speed;
  }

  write(cmd, 2);
}

void PololuQik::setM1Speed(int16_t speed)
{
  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1; // preserve the direction
  }

  if (speed > 255)
    speed = 255;

  if (speed > 127)
  {
    // 8-bit mode: actual speed is (speed + 128)
    cmd[0] = reverse ? QIK_MOTOR_M1_REVERSE_8_BIT : QIK_MOTOR_M1_FORWARD_8_BIT;
    cmd[1] = speed - 128;
  }
  else
  {
    cmd[0] = reverse ? QIK_MOTOR_M1_REVERSE : QIK_MOTOR_M1_FORWARD;
    cmd[1] = speed;
  }

  write(cmd, 2);
}

void PololuQik::setSpeeds(int16_t m0Speed, int16_t m1Speed)
{
  setM0Speed(m0Speed);
  setM1Speed(m1Speed);
}

// 2s9v1

void PololuQik2s9v1::setM0Coast()
{
  write(QIK_2S9V1_MOTOR_M0_COAST);
}

void PololuQik2s9v1::setM1Coast()
{
  write(QIK_2S9V1_MOTOR_M1_COAST);
}

void PololuQik2s9v1::setCoasts()
{
  setM0Coast();
  setM1Coast();
}

// 2s12v10

void PololuQik2s12v10::setM0Brake(uint8_t brake)
{
  if (brake > 127)
    brake = 127;
  
  cmd[0] = QIK_2S12V10_MOTOR_M0_BRAKE;
  cmd[1] = brake;
  write(cmd, 2);
}

void PololuQik2s12v10::setM1Brake(uint8_t brake)
{
  if (brake > 127)
    brake = 127;
  
  cmd[0] = QIK_2S12V10_MOTOR_M1_BRAKE;
  cmd[1] = brake;
  write(cmd, 2);
}

void PololuQik2s12v10::setBrakes(uint8_t m0Brake, uint8_t m1Brake)
{
  setM0Brake(m0Brake);
  setM1Brake(m1Brake);
}

uint8_t PololuQik2s12v10::getM0Current()
{
  write(QIK_2S12V10_GET_MOTOR_M0_CURRENT);
  while (available() < 1);
  return read();
}

uint8_t PololuQik2s12v10::getM1Current()
{
  write(QIK_2S12V10_GET_MOTOR_M1_CURRENT);
  while (available() < 1);
  return read();
}

uint16_t PololuQik2s12v10::getM0CurrentMilliamps()
{
  return getM0Current() * 150;
}

uint16_t PololuQik2s12v10::getM1CurrentMilliamps()
{
  return getM1Current() * 150;
}

uint8_t PololuQik2s12v10::getM0Speed()
{
  write(QIK_2S12V10_GET_MOTOR_M0_SPEED);
  while (available() < 1);
  return read();
}

uint8_t PololuQik2s12v10::getM1Speed()
{
  write(QIK_2S12V10_GET_MOTOR_M1_SPEED);
  while (available() < 1);
  return read();
}