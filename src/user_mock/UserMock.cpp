#include "UserMock.h"
#include <../alexa_sim/AlexaConfig.h>
#include <interfaces/commands/MakeCoffeeCommand.h>
#include <interfaces/commands/OpenDoorCommand.h>
#include <interfaces/commands/CloseDoorCommand.h>

#include <chrono>

using namespace std;
using namespace hsm;
using namespace utility;
using namespace communication;

UserMock::UserMock(const string &name, const TransitionTable &transitionTable, shared_ptr<State> rootState)
        : HSM(name, transitionTable, rootState),
          logger_(Logger::getInstance())
{}

bool UserMock::initialize()
{
    auto isSuccess = true;

    isSuccess &= isSuccess && initializeAlexaQueue();
    isSuccess &= isSuccess && initializeUserQueue();

    return isSuccess;
}

bool UserMock::initializeAlexaQueue()
{
    try
    {
        alexaQueue_ = make_unique<MessageQueueWrapper>(alexa::alexaConfiguration.alexaMsgQueueName);
    }
    catch(boost::interprocess::interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("UserMock:: ") + " During openning alexa queue - " + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + " Alexa massage queue initialized correctly.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool UserMock::initializeUserQueue()
{
    try
    {
        userQueue_ = make_unique<MessageQueueWrapper>(alexa::alexaConfiguration.userMsgQueueName);
    }
    catch(boost::interprocess::interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("UserMock:: ") + " During openning user queue - " + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + " User massage queue initialized correctly.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
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

void UserMock::entryStateFunction(const string &name) noexcept
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + "User entry in ##State: " + name;
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UserMock::exitStateFunction(const string &name) noexcept
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + "User exit from ##State:" + name;
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UserMock::initUser(const std::string &name) noexcept
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + "Invoked procedure for - " + name + " state." + "  ##State: " + name;
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
    defineInternalState("sleep");
}

void UserMock::initSleeping(const string &name) noexcept
{
    (void)name;
    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + "User is still sleeping.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    this_thread::sleep_for(3s);
    handleEvent(transitionTable_.getEvent("MAKE_COFFE"));
}

void UserMock::initMakeCoffee(const string &name) noexcept
{
    (void)name;
    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + "User waked up.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    auto command = MakeCoffeeCommand();
    const auto data = command.getFrameBytes();
    sendMessage(data);

    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + "User sent request for making coffee.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UserMock::initDrinkCoffee(const std::string &name) noexcept
{
    (void)name;
    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + "User started drinking tasty coffee prepared by alexa.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    this_thread::sleep_for(4s);

    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + "I have to go out and close door.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent(transitionTable_.getEvent("CLOSE_DOOR"));
}

void UserMock::initGoOut(const string &name) noexcept
{
    (void)name;
    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + "User go out from house.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    auto command = CloseDoorCommand();
    const auto data = command.getFrameBytes();
    sendMessage(data);
}

void UserMock::initGoIn(const string &name) noexcept
{
    (void)name;
    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + "User again is in a house.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + "It is the end of the story.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UserMock::visit(communication::OpenedDoorResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("UserMock :: Received ") + data.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent(transitionTable_.getEvent("OPEN_DOOR"));
}

void UserMock::visit(communication::ClosedDoorResponse &data)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("UserMock :: Received ") + data.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    this_thread::sleep_for(4s);

    if (logger_.isInformationEnable())
    {
        const std::string message = string("UserMock:: ") + "After several hours user come back to house.";
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
        const std::string message = std::string("UserMock :: Received ") + data.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent(transitionTable_.getEvent("COFFEE_DONE"));
}

void UserMock::sendMessage(const std::vector<uint8_t> &message)
{
    alexaQueue_->send(message);
}
