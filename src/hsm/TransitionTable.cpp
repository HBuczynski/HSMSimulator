#include <sstream>
#include <cassert>

#include "TransitionTable.h"

using namespace std;
using namespace hsm;

TransitionTable::TransitionTable(initializer_list<TranasitionElement> statesTable)
{
    for(auto &element : statesTable)
    {
        assert((get<0>(element)->getParent() != nullptr) && "You dont' initialized parent state.");
        assert((get<2>(element)->getParent() != nullptr) && "You dont' initialized parent state.");

        get<0>(element)->addTransition(get<1>(element), get<2>(element));

        addNotBindState(get<0>(element));
        addNotBindState(get<2>(element));
        addNewEvent(get<1>(element));

        transitionVector_.push_back(move(element));
    }
}

const vector<TranasitionElement> &TransitionTable::getTransitionTable() const noexcept
{
    return transitionVector_;
}

string TransitionTable::showTable() const noexcept
{
    stringstream log;
    uint16_t counter{0};

    log << "## Transition Table ##\n";
    for(const auto& transition : transitionVector_)
    {
        log << to_string(counter++) << ".\t" << get<0>(transition)->getName() << "\t-->\t"
                                            << get<1>(transition) << "\t-->\t"
                                            << get<2>(transition)->getName() << "\n";
    }

    return log.str();
}

void TransitionTable::addNotBindState(shared_ptr<State> state)
{
    const auto isRegistered = states_.find(state->getName());

    if(isRegistered == states_.cend())
    {
        states_[state->getName()] = state;
    }
}

shared_ptr<State> TransitionTable::getState(string id)
{
    const auto isRegistered = states_.find(id);

    if(isRegistered != states_.cend())
    {
        return states_[id];
    }

    return nullptr;
}

void TransitionTable::addNewEvent(Event event)
{
    const auto isRegistered = events_.find(event.getKey());

    if(isRegistered == events_.cend())
    {
        events_.insert({event.getKey(), event});
    }
}

Event TransitionTable::getEvent(string id)
{
    const auto isRegistered = events_.find(id);

    if(isRegistered != events_.cend())
    {
        return (*isRegistered).second;
    }
    else
    {
        return Event{""};
    }
}

