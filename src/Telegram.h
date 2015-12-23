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
    template <class Owner>
    struct Telegram
    {
        Owner *sender;
        Owner *receiver;
        std::string message;
        void *data;

        Telegram() :
        sender(nullptr),
        receiver(nullptr),
        data(nullptr)
        {
            
        }

        ~Telegram()
        {
            
        }
    };
}

#endif