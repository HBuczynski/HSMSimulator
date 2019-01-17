#ifndef HSMSIMULATOR_DRINKINGCOFFEESTATE_H
#define HSMSIMULATOR_DRINKINGCOFFEESTATE_H

#include <hsm/State.h>

namespace user
{
    class DrinkingCoffeeState final : public hsm::State
    {
    public:
        DrinkingCoffeeState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;
    };
}

#endif