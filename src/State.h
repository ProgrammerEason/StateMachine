/*
 * tinycraft.statemachine
 *
 * Copyright (c) 2015 Eason Zhou.
 */

#ifndef STATE_H
#define STATE_H

#include "Telegram.h"

namespace tinycraft
{
    template <class T>
    class StateMachine;
    
    template <class T>
    class State
    {
    private:
        friend class StateMachine<T>;
        std::string _name;
        
    protected:
        virtual bool init(const std::string &name)
        {
            _name = name;
            return true;
        }
        
    public:
        State()
        {
            
        }
        
        virtual ~State()
        {
            
        }
        
        const std::string &getName() const
        {
            return _name;
        }
        
        virtual void enter(T *entity) = 0;
        virtual void update(T *entity, float dt) = 0;
        virtual void exit(T *entity) = 0;
        virtual bool onMessage(Telegram<T> *telegram)
        {
            return true;
        }
    };
}

#endif