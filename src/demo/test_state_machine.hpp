#pragma once

#include <functional>

#include "fsm.hpp"

using namespace fsm;

enum MyState
{
    SLEEPING,
    WORKING,
};

enum MyEventType
{
    TIERED,
    WAKEN,
};

template <class State>
struct MyContext
{
    State current_state;
};

class MyFSM
    : public BasicFiniteStateMachine<MyState, MyContext<MyState>, MyEventType>
{
public:
    MyFSM() { init(); }

private:
    void init();
};
