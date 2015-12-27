/*
 * tinycraft.statemachine
 *
 * Copyright (c) 2015 Eason Zhou.
 */

#ifndef TESTSTATE_H
#define TESTSTATE_H

#include "EntityFactory.h"
#include <MessageDispatcher.h>

class StateGetup : public tinycraft::State<Entity>
{
public:
    StateGetup() { }
    ~StateGetup() { }
    
    void enter(Entity *_owner) override;
    void update(Entity *_owner, float dt) override;
    void exit(Entity *_owner) override;
    bool onMessage(tinycraft::Telegram<Entity> *telegram) override;
};

class StateWash : public tinycraft::State<Entity>
{
public:
    StateWash() { }
    ~StateWash() { }
    
    void enter(Entity *_owner) override;
    void update(Entity *_owner, float dt) override;
    void exit(Entity *_owner) override;
    bool onMessage(tinycraft::Telegram<Entity> *telegram) override;
};

class WifeGlobalState : public tinycraft::State<Entity>
{
public:
    WifeGlobalState() { }
    ~WifeGlobalState() { }
    
    void enter(Entity *_owner) override;
    void update(Entity *_owner, float dt) override;
    void exit(Entity *_owner) override;
    bool onMessage(tinycraft::Telegram<Entity> *telegram) override;
};

class StateCook : public tinycraft::State<Entity>
{
public:
    StateCook() { }
    ~StateCook() { }
    
    void enter(Entity *_owner) override;
    void update(Entity *_owner, float dt) override;
    void exit(Entity *_owner) override;
    bool onMessage(tinycraft::Telegram<Entity> *telegram) override;
};

class StateEat : public tinycraft::State<Entity>
{
public:
    StateEat() { }
    ~StateEat() { }
    
    void enter(Entity *_owner) override;
    void update(Entity *_owner, float dt) override;
    void exit(Entity *_owner) override;
};

#endif