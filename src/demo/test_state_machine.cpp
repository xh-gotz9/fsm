#include "test_state_machine.hpp"

void MyFSM::init()
{
    map_state_transition =
    {
        {
            TIERED,
            {
                [](MyFSM::FSMContext &ctx)
                {
                    if (ctx.current_state == MyFSM::FSMState::WORKING)
                    {
                        ctx.current_state = MyFSM::FSMState::SLEEPING;
                        return true;
                    }

                    return false;
                },
                [](FSMEventType ev_type, MyFSM::FSMContext &ctx) {}
            }
        },
        {
            WAKEN,
            {
                [](MyFSM::FSMContext &ctx)
                {
                    if (ctx.current_state == MyFSM::FSMState::SLEEPING)
                    {
                        ctx.current_state = MyFSM::FSMState::WORKING;
                        return true;
                    }

                    return false;
                },
                [](MyFSM::FSMEventType ev_type, MyFSM::FSMContext &ctx) {}
            }
        }
    };
}

