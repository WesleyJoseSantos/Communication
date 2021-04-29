/**
 * @file CommunicationSerial.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "Communication.h"

class CommunicationSerial : public ICommunication
{
private:
    Stream *stream;
public:
    CommunicationSerial() {}

    void init(Stream *stream){
        this->stream = stream;
    }

    void task(){

    }

    void sendString(String string){
        stream->print(string);
    }

    void sendBytes(uint8_t *bytes, uint8_t size){
        for (size_t i = 0; i < size; i++)
        {
            stream->write(bytes[i]);
        }
    }

    void sendJson(IJson json) override {
        stream->println(json.toJson());
    }

    int dataAvailable(){
        return stream->available();
    }

    String getString(){
        return stream->readString();
    }

    void getBytes(uint8_t *bytes, uint8_t size){
        stream->readBytes(bytes, size);
    }

    void getJson(IJson *json){
        String data = stream->readStringUntil('\n');
        json->fromJson(data);
    }

};