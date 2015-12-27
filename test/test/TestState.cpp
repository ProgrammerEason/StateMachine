/*
 * tinycraft.statemachine
 *
 * Copyright (c) 2015 Eason Zhou.
 */

extern bool isRunning;

#include "TestState.h"
#include <iostream>

void StateGetup::enter(Entity *entity)
{
    std::cout << entity->getName() << ": tring to get up." << std::endl;
    
    void *data = malloc(6);
    memset(data, 0, 6);
    memcpy(data, "pasta", 5);
    
    Entity *wife = EntityFactory::getInstance()->getEntity("wife");
    
    auto instance = tinycraft::MessageDispatcher<Entity>::getInstance();
    instance->dispatchMessage(entity, wife, "hungry", data, 3);
}

void StateGetup::update(Entity *entity, float dt)
{
    std::cout << entity->getName() << ": tring." << std::endl;
}

void StateGetup::exit(Entity *entity)
{
    std::cout << entity->getName() << ": finally i left my bed." << std::endl;
}

bool StateGetup::onMessage(tinycraft::Telegram<Entity> *telegram)
{
    if (telegram->message == "getup") {
        telegram->receiver->getStateMachine()->changeState("wash");
        return true;
    }
    
    return false;
}

void StateWash::enter(Entity *entity)
{
    std::cout << entity->getName() << ": i'm going to wash my face." << std::endl;
}

void StateWash::update(Entity *entity, float dt)
{
    std::cout << entity->getName() << ": washing." << std::endl;
}

void StateWash::exit(Entity *entity)
{
    
}

bool StateWash::onMessage(tinycraft::Telegram<Entity> *telegram)
{
    if (telegram->message == "havebreakfast") {
        telegram->receiver->getStateMachine()->changeState("eat");
        return true;
    }
    
    return false;
}

void WifeGlobalState::enter(Entity *entity)
{
    
}

void WifeGlobalState::update(Entity *entity, float dt)
{
    
}

void WifeGlobalState::exit(Entity *entity)
{
    
}

bool WifeGlobalState::onMessage(tinycraft::Telegram<Entity> *telegram)
{
    if (telegram->message == "hungry") {
        std::cout << telegram->receiver->getName() << ": ready to cook " << (char*)telegram->data << "." << std::endl;
        
        free(telegram->data);
        
        telegram->receiver->getStateMachine()->changeState("cook");
        return true;
    }
    
    return false;
}

void StateCook::enter(Entity *entity)
{
    Entity *husband = EntityFactory::getInstance()->getEntity("husband");
    
    auto instance = tinycraft::MessageDispatcher<Entity>::getInstance();
    instance->dispatchMessage(entity, husband, "getup");
    instance->dispatchMessage(entity, entity, "havebreakfast", nullptr, 5);
    instance->dispatchMessage(entity, husband, "havebreakfast", nullptr, 5);
}

void StateCook::update(Entity *entity, float dt)
{
    std::cout << entity->getName() << ": cooking." << std::endl;
}

void StateCook::exit(Entity *entity)
{
    
}

bool StateCook::onMessage(tinycraft::Telegram<Entity> *telegram)
{
    if (telegram->message == "havebreakfast") {
        telegram->receiver->getStateMachine()->changeState("eat");
        return true;
    }
    
    return false;
}

void StateEat::enter(Entity *entity)
{
    std::cout << entity->getName() << ": have breakfast." << std::endl;
    isRunning = false;
}

void StateEat::update(Entity *entity, float dt)
{
}

void StateEat::exit(Entity *entity)
{
    
}