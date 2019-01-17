#ifndef HSMSIMULATOR_ALEXASTATE_H
#define HSMSIMULATOR_ALEXASTATE_H

#include <hsm/State.h>

namespace alexa
{
    class AlexaState final : public hsm::State
    {
    public:
        AlexaState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif