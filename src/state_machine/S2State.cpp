#include "S2State.h"

using namespace hsm;
using namespace std;
using namespace example;

S2State::S2State(const std::string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void S2State::runEntryEvent() 
{
    cout << "Enter:" << getName() << "  ";
}

void S2State::runExitEvent() 
{
    cout << "Exit:" << getName() << "  ";
}

void S2State::runInitEvent() 
{
    cout << "Init:" << getName() << "  ";
    registerInternalState_("s21");
}


