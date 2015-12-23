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
    template <class Owner>
    class StateMachine;
    
    template <class Owner>
    class State
    {
    private:
        friend class StateMachine<Owner>;
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
        
        ~State()
        {
            
        }
        
        const std::string &getName() const
        {
            return _name;
        }
        
        virtual void enter(Owner *_owner) = 0;
        virtual void update(Owner *_owner, float dt) = 0;
        virtual void exit(Owner *_owner) = 0;
        virtual bool onMessage(Telegram<Owner> *telegram)
        {
            return true;
        }
    };
}

#endif