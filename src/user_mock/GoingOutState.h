#ifndef HSMSIMULATOR_GOINGOUTSTATE_H
#define HSMSIMULATOR_GOINGOUTSTATE_H

#include <hsm/State.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>
#include <alexa_sim/AlexaConfig.h>

namespace user
{
    class GoingOutState final : public hsm::State
    {
    public:
        GoingOutState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void initializeAlexaQueue(std::shared_ptr<communication::MessageQueueWrapper> queue);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;

    private:

        std::shared_ptr<communication::MessageQueueWrapper> alexaQueue_;
    };
}

#endif //HSMSIMULATOR_GOINGOUTSTATE_H
