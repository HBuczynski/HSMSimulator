#include "S21State.h"

using namespace hsm;
using namespace std;
using namespace example;

S21State::S21State(const std::string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void S21State::runEntryEvent() 
{
    cout << "Enter:" << getName() << "  ";
}

void S21State::runExitEvent() 
{
    cout << "Exit:" << getName() << "  ";
}

void S21State::runInitEvent() 
{
    cout << "Init:" << getName() << "  ";
    registerInternalState_("s211");
}


