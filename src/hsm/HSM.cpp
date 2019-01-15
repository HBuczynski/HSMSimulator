#include "HSM.h"
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;
using namespace hsm;

HSM::HSM(const string& name, const TransitionTable &transitionTable, shared_ptr<State> rootState)
    : transitionTable_(transitionTable),
      nextState_(nullptr),
      NAME(name),
      sourceState_(nullptr),
      currentState_(nullptr),
      rootState_(rootState)
{
    assert((rootState != nullptr) && "You dont' initialized root state.");
}

void HSM::start()
{
    currentState_ = rootState_;
    currentState_->runEntryEvent();

    while (currentState_->runInitEvent(), nextState_.get())
    {
        tracePathToTarget();
    }
}

void HSM::handleEvent(Event event) noexcept
{
    vector<shared_ptr<State>> path;

    for(auto pathNode = currentState_; pathNode.get() != nullptr; pathNode = pathNode->getParent())
    {
        sourceState_= pathNode;
        auto state = sourceState_->moveToState(event);

        if(state.get() != nullptr)
        {
            stateTransition(state);
            if(nextState_.get())
            {
                tracePathToTarget();
                while (currentState_->runInitEvent(), nextState_.get())
                {
                   tracePathToTarget();
                }
            };
        }
    }
}

void HSM::tracePathToTarget()
{
    vector<shared_ptr<State>> path;

    for(auto pathElement = nextState_; pathElement != currentState_; pathElement = pathElement->getParent())
    {
        path.push_back(pathElement);
    }

    for(auto iter = path.rbegin(); iter != path.rend(); ++iter)
    {
        (*iter)->runEntryEvent();
    }

    currentState_ = nextState_;
    nextState_ = nullptr;
}

void HSM::defineNextState(const string &name) noexcept
{
    nextState_ = transitionTable_.getState(name);
}

void HSM::stateTransition(shared_ptr<State> state) noexcept
{
    const auto lca = leastCommonAncestor(state);
    exitToLCA(lca);

    nextState_ = state;
}

uint16_t HSM::leastCommonAncestor(std::shared_ptr<State> targetState)
{
    uint16_t lsa{};

    if(sourceState_ != targetState)
    {
        for(auto state = sourceState_; state.get() != nullptr; ++lsa, state = state->getParent())
        {
            for (auto state2 = targetState; state2.get() != nullptr; state2 = state2->getParent())
            {
                if(state == state2)
                {
                    return lsa;
                }
            }
        }
    }
    else
    {
        return 1;
    }

    return 0;
}

void HSM::exitToLCA(uint16_t toLCA)
{
    auto state = currentState_;

    while(state != sourceState_)
    {
        state->runExitEvent();
        state = state->getParent();
    }

    while(toLCA--)
    {
        state->runExitEvent();
        state = state->getParent();
    }

    currentState_ = state;
}
