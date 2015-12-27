/*
 * tinycraft.statemachine
 *
 * Copyright (c) 2015 Eason Zhou.
 */

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "Entity.h"
#include <map>

class EntityFactory
{
private:
    std::map<std::string, Entity*> _entityMap;
    
    EntityFactory();
    EntityFactory(const EntityFactory&);
    EntityFactory& operator =(const EntityFactory&);
    
public:
    ~EntityFactory();
    
    static EntityFactory* getInstance();
    
    Entity* createEntity(const std::string &name);
    
    void destroyEntity(Entity *entity);
    
    Entity* getEntity(const std::string &name);
};

#endif