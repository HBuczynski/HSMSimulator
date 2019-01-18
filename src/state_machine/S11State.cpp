#include "S11State.h"

using namespace hsm;
using namespace std;
using namespace example;

S11State::S11State(const std::string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void S11State::runEntryEvent() 
{
    cout << "Enter:" << getName() << "  ";
}

void S11State::runExitEvent() 
{
    cout << "Exit:" << getName() << "  ";
}

void S11State::runInitEvent() 
{
    cout << "Init:" << getName() << "  ";
}


