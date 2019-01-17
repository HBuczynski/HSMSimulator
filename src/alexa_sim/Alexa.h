#ifndef ALEXA_H
#define ALEXA_H

#include <hsm/HSM.h>
#include <logger/Logger.h>
#include <interfaces/commands/CommandFactory.h>
#include <interfaces/commands/CommandVisitor.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>

#include <atomic>

namespace alexa
{
    class Alexa final : public hsm::HSM, public communication::CommandVisitor
    {
    public:
        Alexa(const std::string& name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState);

        void initializeAlexaQueue(std::shared_ptr<communication::MessageQueueWrapper> queue);
        void initializeUserQueue(std::shared_ptr<communication::MessageQueueWrapper> queue);

        void run();

        void visit(communication::MakeCoffeeCommand &command) override;
        void visit(communication::OpenDoorCommand &command) override;
        void visit(communication::CloseDoorCommand &command) override;
        void visit(communication::EndConnectionCommand &command) override;

    private:
        std::atomic<bool> runSystem_;
        communication::CommandFactory commandFactory_;
        std::shared_ptr<communication::MessageQueueWrapper> alexaQueue_;
        std::shared_ptr<communication::MessageQueueWrapper> userQueue_;

        utility::Logger &logger_;
    };
}

#endif