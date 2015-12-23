/*
 * tinycraft.statemachine
 *
 * Copyright (c) 2015 Eason Zhou.
 */

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.h"
#include <map>
#include <cassert>

namespace tinycraft
{
    template <class Owner>
    class StateMachineFactory;
    
    template <class Owner>
    class StateMachine
    {
    private:
        friend class StateMachineFactory<Owner>;
        
        Owner *_owner;
        std::map<std::string, State<Owner>*> _stateMap;
        State<Owner> *_curState;
        
        void handleMessage(Telegram<Owner> *telegram)
        {
            if (_curState) {
                if (_curState->onMessage(telegram)) {
                    
                }
            }
        }
        
        StateMachine() :
        _owner(nullptr),
        _curState(nullptr)
        {
            
        }
        
    public:
        ~StateMachine()
        {
            
        }
        
        void update(float dt)
        {
            if (_curState) {
                _curState->update(dt);
            }
        }
        
        void registerState(const std::string &name, State<Owner> *state)
        {
            assert(state);
            assert(state->init(name));
            
            _stateMap.insert(std::make_pair(name, state));
        }
        
        void changeState(const std::string &stateName)
        {
            auto result = _stateMap.find(stateName);
            if (result == _stateMap.end()) {
                assert(false);
            }
            
            if (_curState) {
                _curState->exit(_owner);
            }
            
            _curState = result->second;
            _curState->enter(_owner);
        }
    };
}

#endif