#ifndef PololuQik_h
#define PololuQik_h

#include <Arduino.h>
#include "../SoftwareSerial/SoftwareSerial.h"

// Commands

#define QIK_GET_FIRMWARE_VERSION         0x81
#define QIK_GET_ERROR_BYTE               0x82
#define QIK_GET_CONFIGURATION_PARAMETER  0x83
#define QIK_SET_CONFIGURATION_PARAMETER  0x84

#define QIK_MOTOR_M0_FORWARD             0x88
#define QIK_MOTOR_M0_FORWARD_8_BIT       0x89
#define QIK_MOTOR_M0_REVERSE             0x8A
#define QIK_MOTOR_M0_REVERSE_8_BIT       0x8B
#define QIK_MOTOR_M1_FORWARD             0x8C
#define QIK_MOTOR_M1_FORWARD_8_BIT       0x8D
#define QIK_MOTOR_M1_REVERSE             0x8E
#define QIK_MOTOR_M1_REVERSE_8_BIT       0x8F

// 2s9v1 only
#define QIK_2S9V1_MOTOR_M0_COAST         0x86
#define QIK_2S9V1_MOTOR_M1_COAST         0x87

// 2s12v10 only
#define QIK_2S12V10_MOTOR_M0_BRAKE       0x86
#define QIK_2S12V10_MOTOR_M1_BRAKE       0x87
#define QIK_2S12V10_GET_MOTOR_M0_CURRENT 0x90
#define QIK_2S12V10_GET_MOTOR_M1_CURRENT 0x91
#define QIK_2S12V10_GET_MOTOR_M0_SPEED   0x92
#define QIK_2S12V10_GET_MOTOR_M1_SPEED   0x93

// Configuration parameters

#define QIK_CONFIG_DEVICE_ID                        0
#define QIK_CONFIG_PWM_PARAMETER                    1
#define QIK_CONFIG_SHUT_DOWN_MOTORS_ON_ERROR        2
#define QIK_CONFIG_SERIAL_TIMEOUT                   3
#define QIK_CONFIG_MOTOR_M0_ACCELERATION            4
#define QIK_CONFIG_MOTOR_M1_ACCELERATION            5
#define QIK_CONFIG_MOTOR_M0_BRAKE_DURATION          6
#define QIK_CONFIG_MOTOR_M1_BRAKE_DURATION          7
#define QIK_CONFIG_MOTOR_M0_CURRENT_LIMIT_DIV_2     8
#define QIK_CONFIG_MOTOR_M1_CURRENT_LIMIT_DIV_2     9
#define QIK_CONFIG_MOTOR_M0_CURRENT_LIMIT_RESPONSE 10
#define QIK_CONFIG_MOTOR_M1_CURRENT_LIMIT_RESPONSE 11

class PololuQik : public SoftwareSerial
{
  public:
    PololuQik(unsigned char receivePin, unsigned char transmitPin, unsigned char resetPin);

    void init(long speed = 9600);

    char getFirmwareVersion();
    byte getErrors();

    byte getConfigurationParameter(byte parameter);
    byte setConfigurationParameter(byte parameter, byte value);

    void setM0Speed(int speed);
    void setM1Speed(int speed);
    void setSpeeds(int m0Speed, int m1Speed);

  protected:
    unsigned char _resetPin;
};

class PololuQik2s9v1 : public PololuQik
{
  public:
    PololuQik2s9v1(unsigned char receivePin, unsigned char transmitPin, unsigned char resetPin) : PololuQik(receivePin, transmitPin, resetPin) {}

    void setM0Coast();
    void setM1Coast();
    void setCoasts();
};

class PololuQik2s12v10 : public PololuQik
{
  public:
    PololuQik2s12v10(unsigned char receivePin, unsigned char transmitPin, unsigned char resetPin) : PololuQik(receivePin, transmitPin, resetPin) {}

    void setM0Brake(unsigned char brake);
    void setM1Brake(unsigned char brake);
    void setBrakes(unsigned char m0Brake, unsigned char m1Brake);

    unsigned char getM0Current();
    unsigned char getM1Current();
    unsigned int getM0CurrentMilliamps();
    unsigned int getM1CurrentMilliamps();
    unsigned char getM0Speed();
    unsigned char getM1Speed();
};

#endif