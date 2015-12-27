/*
 * tinycraft.statemachine
 *
 * Copyright (c) 2015 Eason Zhou.
 */

#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <string>

namespace tinycraft
{
    template <class T>
    struct Telegram
    {
        T *sender;
        T *receiver;
        std::string message;
        void *data;
        float delay;
        float timer;

        Telegram() :
        sender(nullptr),
        receiver(nullptr),
        data(nullptr),
        delay(0.0),
        timer(0.0)
        {
            
        }

        ~Telegram()
        {
            
        }
    };
}

#endif