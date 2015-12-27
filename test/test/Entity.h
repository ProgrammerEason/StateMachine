/*
 * tinycraft.statemachine
 *
 * Copyright (c) 2015 Eason Zhou.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <StateMachineFactory.h>

class Entity
{
private:
    friend class EntityFactory;
    
    std::string _name;
    tinycraft::StateMachine<Entity> *_stateMachine;

    Entity();
public:
	
	~Entity();

    const std::string& getName() const
    {
        return _name;
    }
    
	tinycraft::StateMachine<Entity>* getStateMachine() const
	{
		return _stateMachine;
	}
};

#endif