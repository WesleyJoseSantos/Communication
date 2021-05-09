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
#include "ESP8266WiFi.h"

enum MsgId
{
  None,
  Digital,
  Pwm
};

DigitalControlData digitalControl;
PwmControlData pwmControl;
JsonMsg control;
CommunicationMqtt comm;

WiFiClient net;
MQTTClient client;

const char ssid[] = "cabo canaveral 2g";
const char pass[] = "16192020";

void connect(){
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduinoMqttTest", "public", "public")) {
    Serial.print(".");
    delay(1000);
  }

}

void setup() {
  Serial.begin(74400);
  WiFi.begin(ssid, pass);

  client.begin("public.cloud.shiftr.io", net);
  connect();
  Serial.println("connected!");

  comm.init(&client, WiFi.macAddress());
  comm.sendString("Connected!");

  Serial.println(comm.getTopic());
}

void clientTask(){
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
}

void loop() {
  clientTask();  
  comm.task();

  if (comm.dataAvailable())
  {
    String data = comm.getString();
    control.fromJson(data);
    Serial.println(data);

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
