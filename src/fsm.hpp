#pragma once

#include <map>
#include <functional>

namespace fsm
{
    template <class EventType>
    struct BasicFSMEvent
    {
        EventType ev_type;
    };

    template <class State, class Context>
    struct BasicFSMContext
    {
        State   state;
        Context   ctx;
    };

    template <class State, class Context, class EventType>
    class BasicFiniteStateMachine
    {
    public:
        using FSMState = State;
        using FSMContext = BasicFSMContext<FSMState, Context>;
        using FSMEventType = EventType;
        using FSMEvent = BasicFSMEvent<FSMEventType>;

        using SimpleStateTransitionFunction = std::function<bool(FSMContext &, const FSMEvent &event)>;

        using StateTransitionFunction = std::function<FSMState(FSMContext &, const FSMEvent &event)>;

        struct StateTransition
        {
            StateTransitionFunction             func_trans_state;
        };

        using StateTransitionMap = std::unordered_map<FSMState, StateTransition>;

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

        bool trigger(FSMContext &ctx, const FSMEvent &event)
        {
            auto state_trans_iter = map_state_transition.find(ctx.state);
            if (map_state_transition.end() == state_trans_iter)
                return false;

            ctx.state = state_trans_iter->second.func_trans_state(ctx, event);

            return true;
        }

        static StateTransitionFunction create_simple_state_trans_template(SimpleStateTransitionFunction func_state_trans, FSMState success_state)
        {
            return std::bind(simple_state_trans_template_with_fail_ignore, func_state_trans, success_state);
        }

        constexpr
        static
        StateTransitionFunction create_simple_state_trans(SimpleStateTransitionFunction func_state_trans, FSMState success_state, FSMState failure_state)
        {
            return std::bind(simple_state_trans_template, func_state_trans, success_state, failure_state, std::placeholders::_1, std::placeholders::_2);
        }

        constexpr
        static
        StateTransition create_state_transition(StateTransitionFunction func)
        {
            return StateTransition { func };
        }

    private:
    
        static
        FSMState simple_state_trans_template_with_fail_ignore(SimpleStateTransitionFunction func_state_trans, FSMState success_state, FSMContext &context, const FSMEvent &event)
        {
            return simple_state_trans_template(func_state_trans, success_state, context.state, context, event);
        }

        static
        FSMState simple_state_trans_template(SimpleStateTransitionFunction func_state_trans, FSMState success_state, FSMState failure_state, FSMContext &context, const FSMEvent &event)
        {
            if (func_state_trans(context, event))
            {
                return success_state;
            }
            else
            {
                return failure_state;
            }
        }
    };

} // namespace fsm
