#ifndef HSMSIMULATOR_S1STATE_H
#define HSMSIMULATOR_S1STATE_H

#include <hsm/State.h>

namespace example
{
    class S1State final : public hsm::State
    {
    public:
        S1State(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif