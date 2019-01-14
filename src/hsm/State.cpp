#include "State.h"
#include <utility/Utility.h>

#include <cassert>

using namespace std;
using namespace hsm;
using namespace utility;

State::State(const string &name, shared_ptr<State> parent)
    : parent_(parent),
      initFunction_(nullptr),
      entryFunction_(nullptr),
      exitFunction_(nullptr),
      name_(move(name)),
      id_(Utility::getStateID()),
      logger_(Logger::getInstance())
{}

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

void State::addInitFunction(Callback init) noexcept
{
    initFunction_ = init;
}

void State::addEntryFunction(Callback entry) noexcept
{
    entryFunction_ = entry;
}

void State::addExitFunction(Callback exit) noexcept
{
    exitFunction_ = exit;
}

void State::runEntryEvent() const noexcept
{
    if(entryFunction_)
    {
        entryFunction_(name_);
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const std::string message = "State:: " + name_ + " - entry function is not defined.";
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void State::runExitEvent() const noexcept
{
    if(exitFunction_)
    {
        exitFunction_(name_);
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const std::string message = "State:: " + name_ + " - entry function is not defined.";
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
}

void State::runInitEvent() const noexcept
{
    if(initFunction_)
    {
        initFunction_(name_);
    }
    else
    {
        if(logger_.isErrorEnable())
        {
            const std::string message = "State:: " + name_ + " - entry function is not defined.";
            logger_.writeLog(LogType::ERROR_LOG, message);
        }
    }
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

    initFunction_ = rhs.initFunction_;
    entryFunction_ = rhs.entryFunction_;
    exitFunction_ = rhs.exitFunction_;

    id_ = rhs.id_;
    name_ = rhs.name_;

    return *this;
}

