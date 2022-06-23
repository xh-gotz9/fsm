#include "test_state_machine.hpp"

void MyFSM::init()
{
    map_state_transition = 
    {
        {
            MyFSM::FSMState::SLEEPING,
            create_state_transition(
                create_simple_state_trans(
                        [](MyFSM::FSMContext &ctx, const MyFSM::FSMEvent &event) -> bool {
                            return MyFSM::FSMEventType::WAKEN == event.ev_type;
                        },
                        MyFSM::FSMState::SLEEPING,
                        MyFSM::FSMState::WORKING
                    )
            )
        },
        {
            MyFSM::FSMState::WORKING,
            {
                [](MyFSM::FSMContext &ctx, const MyFSM::FSMEvent &event) -> MyFSM::FSMState 
                {
                    if (FSMEventType::TIERED == event.ev_type)
                        return MyFSM::FSMState::SLEEPING;

                    return MyFSM::FSMState::WORKING; 
                }
            }
        }
    };
}


