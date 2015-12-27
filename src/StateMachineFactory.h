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
    template <class T>
    class MessageDispatcher;
    
    template <class T>
    class StateMachineFactory
    {
    private:
        friend class MessageDispatcher<T>;
        std::map<T*, StateMachine<T>*> _stateMachineMap;
        
        void handleMessage(Telegram<T> *telegram)
        {
            auto result = _stateMachineMap.find(telegram->receiver);
            if (result != _stateMachineMap.end()) {
                result->second->handleMessage(telegram);
            }
        }
        
        StateMachineFactory()
        {
            
        }
        
        StateMachineFactory(const StateMachineFactory&);
        StateMachineFactory& operator =(const StateMachineFactory&);
        
    public:
        ~StateMachineFactory()
        {
            
        }
        
        static StateMachineFactory* getInstance()
        {
            static StateMachineFactory instance;
            return &instance;
        }
        
        void update(float dt)
        {
            auto iter = _stateMachineMap.begin();
            for (; iter != _stateMachineMap.end(); iter++) {
                iter->second->update(dt);
            }
        }
        
        StateMachine<T>* createStateMachine(T *owner)
        {
            if (!owner) {
                return nullptr;
            }
            
            auto stateMachine = new StateMachine<T>();
            stateMachine->_owner = owner;
            
            _stateMachineMap.insert(std::make_pair(owner, stateMachine));
            return stateMachine;
        }
        
        void destroyStateMachine(T *owner)
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