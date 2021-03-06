/**
 * @file JsonMsg.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "ArduinoJson.h"
#include "IJson.hpp"

class JsonMsg : public IJson
{
public:
    int msgId;

    JsonMsg() {
        msgId = 0;
    }

    void fromJson(String json){
        StaticJsonDocument<64> doc;
        deserializeJson(doc, json);
        
        if(doc.containsKey("msgId")) msgId = doc["msgId"];
    }

    String toJson(){
        StaticJsonDocument<64> doc;
        String json;

        doc["msgId"] = msgId;

        serializeJson(doc, json);

        return json;
    }
};