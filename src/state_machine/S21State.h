#ifndef HSMSIMULATOR_S21STATE_H
#define HSMSIMULATOR_S21STATE_H

#include <hsm/State.h>

namespace example
{
    class S21State final : public hsm::State
    {
    public:
        S21State(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif