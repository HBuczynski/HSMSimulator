#include "Alexa.h"
#include <interfaces/responses/EndConnectionAckResponse.h>

using namespace std;
using namespace hsm;
using namespace alexa;
using namespace utility;
using namespace communication;

Alexa::Alexa(const string &name, const TransitionTable &transitionTable, shared_ptr<State> rootState)
        : HSM(name, transitionTable, rootState),
          runSystem_(false),
          logger_(Logger::getInstance())
{}

void Alexa::initializeAlexaQueue(shared_ptr<MessageQueueWrapper> queue)
{
    alexaQueue_ = queue;
}

void Alexa::initializeUserQueue(std::shared_ptr<communication::MessageQueueWrapper> queue)
{
    userQueue_ = queue;
}

void Alexa::run()
{
    start();
    runSystem_ = true;

    while(runSystem_)
    {
        try
        {
            const auto packet = alexaQueue_->receive();
            const auto command = commandFactory_.createCommand(packet);

            command->accept(*this);
        }
        catch(boost::interprocess::interprocess_exception &ex)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("Alexa :: ") + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
    }
}

void Alexa::visit(MakeCoffeeCommand &command)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received ") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent("MAKE_COFFE");
}

void Alexa::visit(OpenDoorCommand &command)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received ") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent("OPEN_DOOR");
}

void Alexa::visit(CloseDoorCommand &command)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received ") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent("CLOSE_DOOR");
}

void Alexa::visit(communication::EndConnectionCommand &command)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received ") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    runSystem_ = false;

    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("Alexa is going to switch off.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    auto response = EndConnectionAckResponse();
    const auto data = response.getFrameBytes();
    userQueue_->send(data);
}