#include <iostream>
#include "StateMachine.h"

using namespace hsm;
using namespace std;
using namespace example;

StateMachine::StateMachine(const std::string &name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState)
        : HSM(name, transitionTable, rootState)
{}
