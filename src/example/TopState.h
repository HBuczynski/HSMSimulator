#ifndef HSMSIMULATOR_TOPSTATE_H
#define HSMSIMULATOR_TOPSTATE_H

#include <hsm/State.h>

namespace example
{
    class TopState final : public hsm::State
    {
    public:
        TopState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif