#ifndef HSMSIMULATOR_MAKINGCOFFEESTATE_H
#define HSMSIMULATOR_MAKINGCOFFEESTATE_H

#include <hsm/State.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>

namespace user
{
    class MakingCoffeeState final : public hsm::State
    {
    public:
        MakingCoffeeState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void initializeAlexaQueue(std::shared_ptr<communication::MessageQueueWrapper> queue);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;

    private:

        std::shared_ptr<communication::MessageQueueWrapper> alexaQueue_;
    };
}

#endif