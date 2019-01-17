#ifndef HSMSIMULATOR_LOCKERSTATE_H
#define HSMSIMULATOR_LOCKERSTATE_H

#include <hsm/State.h>

namespace alexa
{
    class LockerState final : public hsm::State
    {
    public:
        LockerState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif