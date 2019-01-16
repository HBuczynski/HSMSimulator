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

        bool initialize();
        void run();

        void entryStateFunction(const std::string &name) noexcept;
        void exitStateFunction(const std::string &name) noexcept;

        void initAlexa(const std::string &name) noexcept;
        void initIdle(const std::string &name) noexcept;
        void initLocker(const std::string &name) noexcept;
        void initOpenLocker(const std::string &name) noexcept;
        void initCloseLocker(const std::string &name) noexcept;
        void initCoffeeMaker(const std::string &name) noexcept;
        void initLatte(const std::string &name) noexcept;

        void visit(communication::MakeCoffeeCommand &command) override;
        void visit(communication::OpenDoorCommand &command) override;
        void visit(communication::CloseDoorCommand &command) override;

    private:
        bool initializeAlexaQueue();
        bool initializeUserQueue();

        void sendMessage(const std::vector<uint8_t>& message);

        std::atomic<bool> runSystem_;

        communication::CommandFactory commandFactory_;

        std::shared_ptr<communication::MessageQueueWrapper> alexaQueue_;
        std::shared_ptr<communication::MessageQueueWrapper> userQueue_;

        utility::Logger &logger_;
    };
}

#endif