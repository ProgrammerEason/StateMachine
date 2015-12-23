/*
 * tinycraft.statemachine
 *
 * Copyright (c) 2015 Eason Zhou.
 */

#ifndef STATEMACHINEFACTORY_H
#define STATEMACHINEFACTORY_H

#include "StateMachine.h"
#include <map>
#include <cassert>

namespace tinycraft
{
    template <class Owner>
    class MessageDispatcher;
    
    template <class Owner>
    class StateMachineFactory
    {
    private:
        friend class MessageDispatcher<Owner>;
        std::map<Owner*, StateMachine<Owner>*> _stateMachineMap;
        
        void handleMessage(Telegram<Owner> *telegram)
        {
            auto result = _stateMachineMap.find(telegram->receiver);
            if (result != _stateMachineMap.end()) {
                result->second->handleMessage(telegram);
            }
        }
        
        StateMachineFactory()
        {
            
        }
        
    public:
        ~StateMachineFactory()
        {
            
        }
        
        static StateMachineFactory* create()
        {
            auto factory = new StateMachineFactory();
            return factory;
        }
        
        StateMachine<Owner>* createStateMachine(Owner *owner)
        {
            if (!owner) {
                return nullptr;
            }
            
            auto stateMachine = new StateMachine<Owner>();
            stateMachine->_owner = owner;
            
            _stateMachineMap.insert(std::make_pair(owner, stateMachine));
            return stateMachine;
        }
        
        void destroyStateMachine(Owner *owner)
        {
            auto result = _stateMachineMap.find(owner);
            if (result == _stateMachineMap.end()) {
                assert(false);
            }
            
            assert(result->second);
            delete result->second;
            
            _stateMachineMap.erase(result);
        }
    };
}

#endif