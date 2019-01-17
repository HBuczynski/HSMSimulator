#ifndef HSMSIMULATOR_SLEEPINGSTATE_H
#define HSMSIMULATOR_SLEEPINGSTATE_H

#include <hsm/State.h>

namespace user
{
    class SleepingState final : public hsm::State
    {
    public:
        SleepingState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif