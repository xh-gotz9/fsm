#pragma once

#include <functional>

#include "fsm.hpp"

using namespace fsm;

enum MyState
{
    SLEEPING,
    WORKING,
};

enum MyEvent
{
    TIERED,
    WAKEN,
};

template <class S>
struct MyContext
{
    S current_state;
};

class MyFSM
    : public BasicFiniteStateMachine<MyState, MyContext<MyState>, MyEvent>
{
public:
    MyFSM() { init(); }

private:
    void init();
};
