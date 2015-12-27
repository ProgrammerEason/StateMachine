/*
 * tinycraft.statemachine
 *
 * Copyright (c) 2015 Eason Zhou.
 */

#include "TestState.h"
#include <iostream>

bool isRunning;

int main()
{
    StateGetup *getup = new StateGetup();
    StateWash *wash = new StateWash();
    StateEat *husbandEast = new StateEat();
    
    auto husband = EntityFactory::getInstance()->createEntity("husband");
    husband->getStateMachine()->registerState("getup", getup);
    husband->getStateMachine()->registerState("wash", wash);
    husband->getStateMachine()->registerState("eat", husbandEast);
    
    WifeGlobalState *globalState = new WifeGlobalState();
    StateCook *cook = new StateCook();
    StateEat *wifeEat = new StateEat();
    
    auto wife = EntityFactory::getInstance()->createEntity("wife");
    wife->getStateMachine()->setGlobalState(globalState);
    wife->getStateMachine()->registerState("cook", cook);
    wife->getStateMachine()->registerState("eat", wifeEat);
    
    husband->getStateMachine()->changeState("getup");
    
    isRunning = true;
    long preTime = time(NULL);
    while (isRunning) {
        if (preTime != time(NULL)) {
            preTime = time(NULL);
            
            auto factory = tinycraft::StateMachineFactory<Entity>::getInstance();
            factory->update(1.0);
            
            auto dispatcher = tinycraft::MessageDispatcher<Entity>::getInstance();
            dispatcher->update(1.0);
        }
    }
    
    EntityFactory::getInstance()->destroyEntity(husband);
    EntityFactory::getInstance()->destroyEntity(wife);
    
    return 0;
}