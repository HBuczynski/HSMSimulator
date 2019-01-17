#ifndef HSMSIMULATOR_CLOSELOCKERSTATE_H
#define HSMSIMULATOR_CLOSELOCKERSTATE_H

#include <hsm/State.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>

namespace alexa
{
    class CloseLockerState final : public hsm::State
    {
    public:
        CloseLockerState(const std::string &name, std::shared_ptr<State> parent = nullptr);

        void initializeUserQueue(std::shared_ptr<communication::MessageQueueWrapper> queue);

        void runEntryEvent() override;
        void runExitEvent() override;
        void runInitEvent() override;

    private:

        std::shared_ptr<communication::MessageQueueWrapper> userQueue_;
    };
}

#endif