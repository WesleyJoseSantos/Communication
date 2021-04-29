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

/**
 * Send this Json data on serial port to control blink timer
 * 

{"blinkDelay" : 1000}

**/

#include "ArduinoJson.h"
#include "Communication.h"
#include "BlinkLedData.hpp"
#include "BlinkLedParameters.hpp"

BlinkLedData blinkLedData;                  // Store led blink status and current data
BlinkLedParameters blinkLedParameters;      // Store led blink parameters to control blink effect
CommunicationSerial comm;                   // Default interface communication with serial class

void setup() {
  // Begin serial port
  Serial.begin(9600);
  comm.init(&Serial);

  // Define led pin to output
  pinMode(LED_BUILTIN, OUTPUT);

  // Data initialization
  blinkLedData.pinLed = LED_BUILTIN;
  blinkLedParameters.blinkDelay = 1000;
}

void loop() {
  // Read parameters if is available
  if(comm.dataAvailable()){
    comm.getJson(&blinkLedParameters);
  }

  // Update current led pin status
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  
  // Update blinkLedData structure
  blinkLedData.statusLed = digitalRead(LED_BUILTIN);
  blinkLedData.blinkCount++;
  blinkLedData.timestamp = millis();

  // Send blinkLedData structure to serial port
  comm.sendJson(blinkLedData);

  // Wait parametrized time
  delay(blinkLedParameters.blinkDelay);
}