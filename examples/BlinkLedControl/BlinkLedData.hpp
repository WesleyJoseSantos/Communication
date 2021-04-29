/**
 * @file ClimateData.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "ArduinoJson.h"
#include "IJson.hpp"

class BlinkLedData : public IJson
{
public:
    int pinLed;
    bool statusLed;
    int blinkCount;
    unsigned long timestamp;
    
    BlinkLedData(){}

    void fromJson(String json){
        StaticJsonDocument<64> doc;
        deserializeJson(doc, json);
        
        if(doc.containsKey("pinLed")) pinLed = doc["pinLed"];
        if(doc.containsKey("statusLed")) statusLed = doc["statusLed"];
        if(doc.containsKey("blinkCount")) blinkCount = doc["blinkCount"];
        if(doc.containsKey("timestamp")) timestamp = doc["timestamp"];
    }

    String toJson(){
        StaticJsonDocument<64> doc;
        String json;

        doc["pinLed"] = pinLed;
        doc["statusLed"] = statusLed;
        doc["blinkCount"] = blinkCount;
        doc["timestamp"] = timestamp;

        serializeJson(doc, json);

        return json;
    }
};
