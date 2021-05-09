/**
 * @file CommunicationHttpServer.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "Communication.h"

#ifdef ESP32
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

#define DEFAULT_RX_URI "/rxUri"
#define DEFAULT_TX_URI "/txUri"

class CommunicationHttpServer : ICommunication
{
private:
    AsyncWebServer *server;
    static String uriRx;
    static String uriTx;
    static String dataToReceive;
    static String dataToSend;
    static int dataReceived;

    static void onMessage(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
        uint8_t sizedData[len + 1];
        
        for (size_t i = 0; i < len; i++)
        {
            sizedData[i] = data[i];
        }
        sizedData[len] = '\0';
        
        dataToReceive = (char*)sizedData;
        dataReceived = true;
        request->send(200, "text/plain", "OK");
    }

    static void onRequest(AsyncWebServerRequest *request){
        request->send(200, "text/plain", dataToSend);
    }

public:
    CommunicationHttpServer() {}

    void init(AsyncWebServer *server){
        this->server = server;
        this->uriRx = DEFAULT_RX_URI;
        this->uriTx = DEFAULT_TX_URI;
        dataToSend = "NULL";

        server->on(uriRx.c_str(), HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, onMessage);
        server->on(uriTx.c_str(), HTTP_GET, this->onRequest);
        server->begin();
    }

    void task(){

    }

    void setUri(String uri){
        this->uriTx = uri;
    }

    String getUri(){
        return uriRx;
    }

    void sendString(String string){
        dataToSend = string;
    }

    void sendBytes(uint8_t *bytes, uint8_t size){
        //TODO
    }

    void sendJson(IJson *json) override {
        dataToSend = json->toJson();
    }

    int dataAvailable(){
        return dataReceived;
    }

    String getString(){
        dataReceived = 0;
        return dataToReceive;
    }

    void getBytes(uint8_t *bytes, uint8_t size){
        //TODO
    }

    void getJson(IJson *json){
        dataReceived = 0;
        json->fromJson(dataToReceive);
    }
};

String CommunicationHttpServer::uriRx;
String CommunicationHttpServer::uriTx;
String CommunicationHttpServer::dataToSend;
String CommunicationHttpServer::dataToReceive;
int CommunicationHttpServer::dataReceived;