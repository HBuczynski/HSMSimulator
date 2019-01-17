#include "S1State.h"

using namespace hsm;
using namespace std;
using namespace example;

S1State::S1State(const std::string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void S1State::runEntryEvent() 
{
    cout << "Enter:" << getName() << "  ";
}

void S1State::runExitEvent() 
{
    cout << "Exit:" << getName() << "  ";
}

void S1State::runInitEvent() 
{
    cout << "Init:" << getName() << "  ";
    registerInternalState_("s11");
}


