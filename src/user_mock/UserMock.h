#ifndef HSMSIMULATOR_USERMOCK_H
#define HSMSIMULATOR_USERMOCK_H

#include "hsm/HSM.h"

#include <message_queue_wrapper/MessageQueueWrapper.h>
#include <interfaces/responses/ResponseVisitor.h>
#include <interfaces/responses/ResponseFactory.h>

#include <atomic>

namespace user
{
    class UserMock
            : public hsm::HSM, public communication::ResponseVisitor
    {
    public:
        UserMock(const std::string &name, const hsm::TransitionTable &transitionTable,
                 std::shared_ptr<hsm::State> rootState);

        void initializeAlexaQueue(std::shared_ptr<communication::MessageQueueWrapper> queue);
        void initializeUserQueue(std::shared_ptr<communication::MessageQueueWrapper> queue);
        void run();

        void visit(communication::OpenedDoorResponse &data) override;
        void visit(communication::ClosedDoorResponse &data) override;
        void visit(communication::CoffeeDoneResponse &data) override;
        void visit(communication::EndConnectionAckResponse &data) override;

    private:
        void sendMessage(const std::vector<uint8_t> &message);

        std::atomic<bool> runSystem_;

        communication::ResponseFactory responseFactory_;

        std::shared_ptr<communication::MessageQueueWrapper> alexaQueue_;
        std::shared_ptr<communication::MessageQueueWrapper> userQueue_;

        utility::Logger &logger_;
    };
}

#endif
