#ifndef HSMSIMULATOR_LATTESTATE_H
#define HSMSIMULATOR_LATTESTATE_H

#include <hsm/State.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>

namespace alexa
{
    class LatteState final : public hsm::State
    {
    public:
        LatteState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void initializeUserQueue(std::shared_ptr<communication::MessageQueueWrapper> queue);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;

    private:

        std::shared_ptr<communication::MessageQueueWrapper> userQueue_;
    };
}

#endif