#ifndef HSMSIMULATOR_S11STATE_H
#define HSMSIMULATOR_S11STATE_H

#include <hsm/State.h>

namespace example
{
    class S11State final : public hsm::State
    {
    public:
        S11State(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif