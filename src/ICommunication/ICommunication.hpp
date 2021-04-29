/**
 * @file ICommunication.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
 
#include "IJson.h"
#include "WString.h"

class ICommunication
{
private:
    
public:
    ICommunication() {}
    virtual void task() = 0;
    virtual void sendString(String string) = 0;
    virtual void sendBytes(uint8_t *bytes, uint8_t size) = 0;
    virtual void sendJson(IJson json) = 0;
    virtual int dataAvailable() = 0;
    virtual String getString() = 0;
    virtual void getBytes(uint8_t *bytes, uint8_t size) = 0;
    virtual void getJson(IJson *json) = 0;
 };