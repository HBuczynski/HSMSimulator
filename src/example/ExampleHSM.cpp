#include <iostream>
#include "ExampleHSM.h"

using namespace hsm;
using namespace std;

ExampleHSM::ExampleHSM(const std::string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState)
        : HSM(name, transitionTable, rootState)
{}

void ExampleHSM::initTop(const string &name) noexcept
{
    cout << "Init:" <<  name << " --> ";
    defineNextState("s1");
}

void ExampleHSM::inits1(const string &name) noexcept
{
    cout << "Init:" <<  name << " --> ";
    defineNextState("s11");
}

void ExampleHSM::inits11(const string &name) noexcept
{
    cout << "Init:" <<  name << " --> ";
}

void ExampleHSM::inits2(const string &name) noexcept
{
    cout << "Init:" <<  name << " --> ";
    defineNextState("s21");
}

void ExampleHSM::inits21(const string &name) noexcept
{
    cout << "Init:" <<  name << " --> ";
    defineNextState("s211");
}

void ExampleHSM::init211(const string &name) noexcept
{
    cout << "Init:" <<  name << " --> ";
}

void ExampleHSM::entryStateFunction(const string &name) noexcept
{
    cout << "Enter:" << name << " --> ";
}

void ExampleHSM::exitStateFunction(const string &name) noexcept
{
    cout << "Exit:" << name << " --> ";
}