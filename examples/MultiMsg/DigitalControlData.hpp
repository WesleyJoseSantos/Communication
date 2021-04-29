/**
 * @file PwmControlData.hpp
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

class PwmControlData : public JsonMsg
{
public:
    int pin;
    int value;

    PwmControlData(){}

    void fromJson(String json){
        StaticJsonDocument<64> doc;
        deserializeJson(doc, json);
        
        if(doc.containsKey("pin")) pin = doc["pin"];
        if(doc.containsKey("value")) value = doc["value"];
        if(doc.containsKey("msgId")) msgId = doc["msgId"];
    }

    String toJson(){
        StaticJsonDocument<64> doc;
        String json;

        doc["pin"] = pin;
        doc["value"] = value;
        doc["msgId"] = msgId;

        serializeJson(doc, json);

        return json;
    }

};
