/**
 * @file CommunicationMqtt.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __COMMUNICATIONMQTT__H__
#define __COMMUNICATIONMQTT__H__

#pragma once

#include "Communication.h"
#include <MQTT.h>

class CommunicationMqtt : public ICommunication
{
private:
    MQTTClient *client;
    String topicRx;
    String topicTx;

public:
    CommunicationMqtt() {

    }

    void init(MQTTClient *client){
        this->client = client;

        //this->client->onMessage(); O QUE FAZER???????

        this->topicRx = "/defaultRxTopic";
        this->topicTx = "/defaultTxTopic";
    }

    void task(){

    }

    void setTopic(String topic){
        this->topicTx = topic;
    }

    String getTopic(){
        return topicRx;
    }

    void sendString(String string){
        client->publish(topicTx, string);
    }

    void sendBytes(uint8_t *bytes, uint8_t size){
        String data;
        for (size_t i = 0; i < size; i++)
        {
            data = data + char(bytes[i]);
        }
        
        client->publish(topicTx, data);
    }

    void sendJson(IJson *json) override {
        client->publish(topicTx, json->toJson());
    }

    int dataAvailable(){

    }

    String getString(){

    }

    void getBytes(uint8_t *bytes, uint8_t size){

    }

    void getJson(IJson *json){
        String data;
        json->fromJson(data);
    }

    void messageReceived(String &topic, String &payload){

    }
};

#endif  //!__COMMUNICATIONMQTT__H__