#include <stdio.h>

#include <gtest/gtest.h>

#include "test_state_machine.hpp"

TEST(SM_TEST, implement_my_sm)
{
    MyFSM my_fsm;
    MyFSM::FSMContext ctx;
    ctx.state = MyFSM::FSMState::WORKING;

    my_fsm.trigger(ctx, { MyFSM::FSMEventType::TIERED });

    ASSERT_EQ(ctx.state, MyFSM::FSMState::SLEEPING);
}
