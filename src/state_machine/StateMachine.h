#ifndef ALEXASIMULATOR_ALEXAHSM_H
#define ALEXASIMULATOR_ALEXAHSM_H

#include <hsm/HSM.h>

namespace example
{
    class StateMachine final : public hsm::HSM
    {
    public:
        StateMachine(const std::string &name, const hsm::TransitionTable &transitionTable,
                   std::shared_ptr<hsm::State> rootState);

    };
}
#endif