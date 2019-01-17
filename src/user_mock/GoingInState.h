#ifndef HSMSIMULATOR_GOINGINSTATE_H
#define HSMSIMULATOR_GOINGINSTATE_H

#include <hsm/State.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>

namespace user
{
    class GoingInState final : public hsm::State
    {
    public:
        GoingInState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void initializeAlexaQueue(std::shared_ptr<communication::MessageQueueWrapper> queue);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;

    private:

        std::shared_ptr<communication::MessageQueueWrapper> alexaQueue_;
    };
}

#endif