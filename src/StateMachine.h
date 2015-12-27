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
    template <class T>
    class StateMachineFactory;
    
    template <class T>
    class StateMachine
    {
    private:
        friend class StateMachineFactory<T>;
        
        T *_owner;
        std::map<std::string, State<T>*> _stateMap;
        State<T> *_globalState;
        State<T> *_curState;
        
        void handleMessage(Telegram<T> *telegram)
        {
            if (_globalState) {
                if (_globalState->onMessage(telegram)) {
                    return;
                }
            }
            
            if (_curState) {
                _curState->onMessage(telegram);
            }
        }
        
        void update(float dt)
        {
            if (_globalState) {
                _globalState->update(_owner, dt);
            }
            
            if (_curState) {
                _curState->update(_owner, dt);
            }
        }
        
        StateMachine() :
        _owner(nullptr),
        _globalState(nullptr),
        _curState(nullptr)
        {
            
        }
        
    public:
        ~StateMachine()
        {
            auto result = _stateMap.begin();
            for (; result != _stateMap.end(); result++) {
                delete result->second;
            }
            
            _stateMap.clear();
        }
        
        void setGlobalState(State<T> *state)
        {
            if (_globalState) {
                _globalState->exit(_owner);
            }
            
            assert(state);
            _globalState = state;
            _globalState->enter(_owner);
        }
        
        void registerState(const std::string &name, State<T> *state)
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