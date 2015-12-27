/*
 * tinycraft.statemachine
 *
 * Copyright (c) 2015 Eason Zhou.
 */

#include "EntityFactory.h"
#include <cassert>

EntityFactory::EntityFactory()
{
    
}

EntityFactory::~EntityFactory()
{
    
}

EntityFactory* EntityFactory::getInstance()
{
    static EntityFactory instance;
    return &instance;
}

Entity* EntityFactory::createEntity(const std::string &name)
{
    Entity *entity = new Entity();
    
    auto instance = tinycraft::StateMachineFactory<Entity>::getInstance();
    entity->_stateMachine = instance->createStateMachine(entity);
    entity->_name = name;
    
    _entityMap.insert(std::make_pair(name, entity));
    
    return entity;
}

void EntityFactory::destroyEntity(Entity *entity)
{
    assert(entity);
    
    auto instance = tinycraft::StateMachineFactory<Entity>::getInstance();
    instance->destroyStateMachine(entity);
    
    auto result = _entityMap.find(entity->getName());
    if (result ==_entityMap.end()) {
        assert(false);
    }
    
    _entityMap.erase(result);
    
    delete entity;
}

Entity* EntityFactory::getEntity(const std::string &name)
{
    auto result = _entityMap.find(name);
    if (result == _entityMap.end())
    {
        return nullptr;
    }
    
    return result->second;
}