#include "TopState.h"

using namespace hsm;
using namespace std;
using namespace example;

TopState::TopState(const std::string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void TopState::runEntryEvent() 
{
    cout << "Enter:" << getName() << "  ";
}

void TopState::runExitEvent() 
{
    cout << "Exit:" << getName() << "  ";
}

void TopState::runInitEvent() 
{
    cout << "Init:" << getName() << "  ";
    registerInternalState_("s1");
}


