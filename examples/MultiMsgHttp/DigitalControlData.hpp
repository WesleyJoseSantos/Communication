/**
 * @file DigitalControlData.hpp
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
#include "JsonMsg.hpp"

class DigitalControlData : public JsonMsg
{
public:
    int pin;
    bool status;

    DigitalControlData(){}

    void fromJson(String json){
        StaticJsonDocument<128> doc;
        deserializeJson(doc, json);
        
        if(doc.containsKey("pin")) pin = doc["pin"];
        if(doc.containsKey("status")) status = doc["status"];
        if(doc.containsKey("msgId")) msgId = doc["msgId"];
    }

    String toJson(){
        StaticJsonDocument<128> doc;
        String json;

        doc["pin"] = pin;
        doc["status"] = status;
        doc["msgId"] = msgId;

        serializeJson(doc, json);

        return json;
    }

};
