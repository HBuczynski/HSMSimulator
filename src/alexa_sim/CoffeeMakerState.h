#ifndef HSMSIMULATOR_COFFEEMAKERSTATE_H
#define HSMSIMULATOR_COFFEEMAKERSTATE_H

#include <hsm/State.h>

namespace alexa
{
    class CoffeeMakerState final : public hsm::State
    {
    public:
        CoffeeMakerState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif