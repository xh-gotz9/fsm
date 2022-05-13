#pragma once

#include <map>
#include <functional>

namespace fsm
{
    template <class T, class F>
    struct BasicStateTransition
    {
        T func_transition;
        F func_failure;
    };

    template <class E, class C>
    struct BasicFSMEvent
    {
        E ev_type;
        C ctx;
    };

    template <class S, class C, class E>
    class BasicFiniteStateMachine
    {
    public:
        using FSMState = S;
        using FSMContext = C;
        using FSMEventType = E;

        using FSMEvent = BasicFSMEvent<FSMEventType, FSMContext>;
        using StateTransitionCallback = std::function<bool(FSMContext &)>;
        using StateTransitionFailure = std::function<void(FSMEventType, FSMContext &)>;

        using StateTransition = BasicStateTransition<StateTransitionCallback, StateTransitionFailure>;
        using StateTransitionMap = std::map<FSMEventType, StateTransition>;

    protected:
        StateTransitionMap map_state_transition;

    public:
        BasicFiniteStateMachine() {}

        BasicFiniteStateMachine(StateTransitionMap &&map) : map_state_transition(map)
        {
        }

        void setStateTransitionMap(StateTransitionMap &&map)
        {
            map_state_transition = map;
        }

        bool trigger(const FSMEventType &ev_type, FSMContext &ctx)
        {
            auto iter = map_state_transition.find(ev_type);
            if (map_state_transition.end() == iter)
                return false;

            if (!iter->second.func_transition(ctx))
            {
                iter->second.func_failure(ev_type, ctx);
                return false;
            }

            return true;
        }
    };

} // namespace fsm
