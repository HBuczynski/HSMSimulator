#include "S211State.h"

using namespace hsm;
using namespace std;
using namespace example;

S211State::S211State(const std::string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void S211State::runEntryEvent() 
{
    cout << "Enter:" << getName() << "  ";
}

void S211State::runExitEvent() 
{
    cout << "Exit:" << getName() << "  ";
}

void S211State::runInitEvent() 
{
    cout << "Init:" << getName() << "  ";
}
