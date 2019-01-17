#include "State.h"
#include <utility/Utility.h>

#include <cassert>

using namespace std;
using namespace hsm;
using namespace utility;

Callback State::handleEvent_ = nullptr;
Callback State::registerInternalState_ = nullptr;
bool State::isCallbackInitialized = false;

State::State(const string &name, shared_ptr<State> parent)
    : logger_(Logger::getInstance()),
      id_(Utility::getStateID()),
      name_(move(name)),
      parent_(parent)
{}

void State::initializeHSMCallbacks(Callback handleEvent, Callback registerInternalState)
{
    if (!isCallbackInitialized )
    {
        handleEvent_ = handleEvent;
        registerInternalState_ = registerInternalState;

        isCallbackInitialized = true;
    }
}

void State::addTransition(Event event, shared_ptr<State> state)
{
    const auto isRegistered = stateTable_.find(event);

    if(isRegistered == stateTable_.cend())
    {
        stateTable_[event] = state;
    }
    else if( (stateTable_[event].lock() != nullptr) && (stateTable_[event].lock()->getID() == state->getID()) )
    {
        if (logger_.isWarningEnable())
        {
            const std::string message = "State:: " + name_ + " - tried to add the same transition second time.";
            logger_.writeLog(LogType::WARNING_LOG, message);
        }
    }
    else
    {
        if (logger_.isErrorEnable())
        {
            const std::string message = "State:: " + name_ + " - cannot assign event to - " + state->getName();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        assert(0 && "You have tried to add another state to existing event.");
    }
}

shared_ptr<State> State::moveToState(Event event)
{
    const auto isRegistered = stateTable_.find(event);

    if(isRegistered != stateTable_.cend())
    {
        auto nextState = stateTable_[event];
        return nextState.lock();
    }

    return nullptr;
}

const string &State::getName() const noexcept
{
    return name_;
}

const uint32_t &State::getID() const noexcept
{
    return id_;
}

shared_ptr<State> State::getParent() const noexcept
{
    return parent_.lock();
}

bool State::operator==(const State &rhs)
{
    return id_ == rhs.id_;
}

State &State::operator=(const State &rhs)
{
    parent_ = rhs.parent_;
    stateTable_ = rhs.stateTable_;

    id_ = rhs.id_;
    name_ = rhs.name_;

    return *this;
}
