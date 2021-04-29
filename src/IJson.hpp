/**
 * @file IJson.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <WString.h>

class IJson
{
private:
    
public:
    IJson(){}

    virtual void fromJson(String json) = 0;
    virtual String toJson() = 0;
};