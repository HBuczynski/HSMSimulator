#ifndef HSMSIMULATOR_USERSTATE_H
#define HSMSIMULATOR_USERSTATE_H

#include <hsm/State.h>

namespace user
{
    class UserState final : public hsm::State
    {
    public:
        UserState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif