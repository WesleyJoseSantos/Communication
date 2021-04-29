/**
 * @file BlinkLedParameters.hpp
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

class BlinkLedParameters : public IJson
{
public:
    int blinkDelay;

    BlinkLedParameters(){
        blinkDelay = 1000;
    }

    void fromJson(String json){
        StaticJsonDocument<32> doc;
        deserializeJson(doc, json);
        
        if(doc.containsKey("blinkDelay")) blinkDelay = doc["blinkDelay"];
    }

    String toJson(){
        StaticJsonDocument<32> doc;
        String json;

        doc["blinkDelay"] = blinkDelay;

        serializeJson(doc, json);

        return json;
    }
};
