/*
 * tinycraft.statemachine
 *
 * Copyright (c) 2015 Eason Zhou.
 */

#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include "StateMachineFactory.h"
#include <set>
#include <cassert>

namespace tinycraft
{
	template <class T>
	class MessageDispatcher
    {
    private:
        std::set<Telegram<T>*> _telegramSet;
        
        MessageDispatcher()
        {
            
        }
        
        MessageDispatcher(const MessageDispatcher&);
        MessageDispatcher& operator =(const MessageDispatcher&);
        
	public:
        ~MessageDispatcher()
        {
            
        }
        
        static MessageDispatcher* getInstance()
        {
            static MessageDispatcher instance;
            return &instance;
        }
        
        void update(float dt)
        {
            auto iter = _telegramSet.begin();
            for (; iter != _telegramSet.end();) {
                auto telegram = *iter;
                
                telegram->timer += dt;
                if (telegram->timer >= telegram->delay) {
                    auto instance = tinycraft::StateMachineFactory<Entity>::getInstance();
                    instance->handleMessage(telegram);
                    delete telegram;
                    
                    iter = _telegramSet.erase(iter);
                }
                else {
                    iter++;
                }
            }
        }
        
		void dispatchMessage(T *sender, T *receiver, const std::string &message, void *data = nullptr, float delay = 0.0f)
        {
			assert(sender || receiver);

			Telegram<T> *telegram = new Telegram<T>();
			telegram->sender = sender;
			telegram->receiver = receiver;
			telegram->message = message;
			telegram->data = data;
            telegram->delay = delay;
            telegram->timer = 0.0f;
            
            if (delay > 0.0f) {
                _telegramSet.insert(telegram);
            }
            else {
                auto instance = tinycraft::StateMachineFactory<Entity>::getInstance();
                instance->handleMessage(telegram);
                
                delete telegram;

            }
        }
	};
}

#endif