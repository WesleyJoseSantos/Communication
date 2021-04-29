/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ArduinoJson.h"
#include "Communication.h"
#include "DigitalControlData.hpp"
#include "PwmControlData.hpp"

enum MsgId
{
  None,
  Digital,
  Pwm
};

DigitalControlData digitalControl;
PwmControlData pwmControl;
JsonMsg control;
CommunicationSerial comm;

void setup() {
  // Begin serial port
  Serial.begin(9600);
  comm.init(&Serial);
}

void loop() {
  // Read parameters if is available

  if (comm.dataAvailable())
  {
    String data = comm.getString();
    control.fromJson(data);

    switch (control.msgId)
    {
    case MsgId::None:
      
      break;
    case MsgId::Digital:
      digitalControl.fromJson(data);
      pinMode(digitalControl.pin, OUTPUT);
      digitalWrite(digitalControl.pin, digitalControl.status);
      break;
    case MsgId::Pwm:
      pwmControl.fromJson(data);
      pinMode(pwmControl.pin, OUTPUT);
      analogWrite(pwmControl.pin, pwmControl.value);
      break;
    default:
      break;
    }
  }
}