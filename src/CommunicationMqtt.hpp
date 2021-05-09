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

#pragma once

#include "Communication.h"
#include <MQTT.h>

#define DEFAULT_RX_TOPIC "/mac/rxTopic"
#define DEFAULT_TX_TOPIC "/mac/txTopic"

class CommunicationMqtt : public ICommunication
{
private:
    MQTTClient *client;
    static String topicRx;
    static String topicTx;
    static String data;
    static int dataReceived;

    static void onMessage(String &topic, String &payload){
        dataReceived = payload.length();
        topicRx = topic;
        data = payload;
    }

public:
    CommunicationMqtt() {

    }

    void init(MQTTClient *client){
        this->client = client;
        this->client->onMessage(this->onMessage);
    }

    void init(MQTTClient *client, String topicRx, String topicTx){
        this->client = client;
        this->client->onMessage(this->onMessage);
        this->topicRx = topicRx;
        this->topicTx = topicTx;
        this->client->subscribe(this->topicRx);
    }

    void init(MQTTClient *client, String mac){
        this->client = client;
        this->client->onMessage(this->onMessage);
        
        this->topicRx = DEFAULT_RX_TOPIC;
        this->topicTx = DEFAULT_TX_TOPIC;
        this->topicRx.replace("mac", mac);
        this->topicTx.replace("mac", mac);

        this->client->subscribe(this->topicRx);
    }

    void task(){

    }

    void setTopic(String topic){
        this->topicTx = topic;
        this->client->subscribe(this->topicRx);
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
        return dataReceived;
    }

    String getString(){
        dataReceived = 0;
        return data;
    }

    void getBytes(uint8_t *bytes, uint8_t size){
        dataReceived -= size;
        for (size_t i = 0; i < size; i++)
        {
            bytes[i] = data[i];
        }
    }

    void getJson(IJson *json){
        dataReceived = 0;
        json->fromJson(data);
    }
};

String CommunicationMqtt::topicRx;
String CommunicationMqtt::topicTx;
String CommunicationMqtt::data;
int CommunicationMqtt::dataReceived;