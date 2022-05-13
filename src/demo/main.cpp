#include <stdio.h>

#include <gtest/gtest.h>

#include "test_state_machine.hpp"

TEST(SM_TEST, implement_my_sm)
{
    MyFSM my_fsm;
    MyFSM::FSMContext ctx;
    ctx.current_state = MyFSM::FSMState::WORKING;

    ASSERT_TRUE(my_fsm.trigger(MyFSM::FSMEventType::TIERED, ctx));

    ASSERT_EQ(ctx.current_state, MyFSM::FSMState::SLEEPING);
}
