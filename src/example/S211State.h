#ifndef HSMSIMULATOR_S211STATE_H
#define HSMSIMULATOR_S211STATE_H

#include <hsm/State.h>

namespace example
{
    class S211State final : public hsm::State
    {
    public:
        S211State(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif //HSMSIMULATOR_S211STATE_H
