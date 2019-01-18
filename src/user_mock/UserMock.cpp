#include "UserMock.h"
#include <interfaces/commands/OpenDoorCommand.h>

#include <chrono>

using namespace std;
using namespace hsm;
using namespace user;
using namespace utility;
using namespace communication;

UserMock::UserMock(const string &name, const TransitionTable &transitionTable, shared_ptr<State> rootState)
        : HSM(name, transitionTable, rootState),
          logger_(Logger::getInstance())
{}

void UserMock::initializeAlexaQueue(shared_ptr<communication::MessageQueueWrapper> queue)
{
    alexaQueue_ = queue;
}

void UserMock::initializeUserQueue(shared_ptr<communication::MessageQueueWrapper> queue)
{
    userQueue_ = queue;
}

void UserMock::run()
{
    start();
    runSystem_ = true;

    while(runSystem_)
    {
        try
        {
            const auto packet = userQueue_->receive();
            const auto response = responseFactory_.createCommand(packet);

            response->accept(*this);
        }
        catch(boost::interprocess::interprocess_exception &ex)
        {
            if(logger_.isErrorEnable())
            {
                const string message = string("User :: ") + ex.what();
                logger_.writeLog(LogType::ERROR_LOG, message);
            }
        }
    }
}

void UserMock::visit(communication::OpenedDoorResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("User:: Received ") + data.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent("OPEN_DOOR");
}

void UserMock::visit(communication::ClosedDoorResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("User:: Received ") + data.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "After several hours user come back to house.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    auto command = OpenDoorCommand();
    const auto dataCommand = command.getFrameBytes();
    sendMessage(dataCommand);
}

void UserMock::visit(communication::CoffeeDoneResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("User:: Received ") + data.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent("COFFEE_DONE");
}

void UserMock::sendMessage(const vector<uint8_t> &message)
{
    alexaQueue_->send(message);
}

void UserMock::visit(communication::EndConnectionAckResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const string message = string("User:: Received ") + data.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    if(logger_.isInformationEnable())
    {
        const string message = string("User:: User shuts down the application.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    runSystem_ = false;
}