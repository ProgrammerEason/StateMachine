/*
 * tinycraft.statemachine
 *
 * Copyright (c) 2015 Eason Zhou.
 */

#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include "StateMachineFactory.h"
#include <cassert>

namespace tinycraft
{
	template <class Owner>
	class MessageDispatcher
    {
    private:
        StateMachineFactory<Owner> *_factory;
        
        MessageDispatcher() :
        _factory(nullptr)
        {
            
        }
        
	public:
        ~MessageDispatcher()
        {
            
        }
        
        static MessageDispatcher* create(StateMachineFactory<Owner> *factory) {
            assert(factory);
            
            auto dispatcher = new MessageDispatcher();
            dispatcher->_factory = factory;
            return dispatcher;
        }
        
		void dispatchMessage(Owner *sender, Owner *receiver, const std::string &message, void *data = nullptr)
        {
			assert(sender || receiver);

			Telegram<Owner> *telegram = new Telegram<Owner>();
			telegram->sender = sender;
			telegram->receiver = receiver;
			telegram->message = message;
			telegram->data = data;
            
            _factory->handleMessage(telegram);
            
            delete telegram;
		}
	};
}

#endif