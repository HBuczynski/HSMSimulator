#include <interfaces/responses/CoffeeDoneResponse.h>
#include <interfaces/responses/OpenedDoorResponse.h>
#include <interfaces/responses/ClosedDoorResponse.h>

#include "Alexa.h"
#include "AlexaConfig.h"

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

bool Alexa::initialize()
{
    auto isSuccess = true;

    isSuccess &= isSuccess && initializeAlexaQueue();
    isSuccess &= isSuccess && initializeUserQueue();

    return isSuccess;
}

bool Alexa::initializeAlexaQueue()
{
    try
    {
        alexaQueue_ = make_shared<MessageQueueWrapper>(alexaConfiguration.alexaMsgQueueName,
                alexaConfiguration.queueLength,
                alexaConfiguration.messageQueueSize);
    }
    catch(boost::interprocess::interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("Alexa:: Alexa message queue has not been initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("Alexa:: Alexa message queue has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
}

bool Alexa::initializeUserQueue()
{
    try
    {
        userQueue_ = make_shared<MessageQueueWrapper>(alexaConfiguration.userMsgQueueName,
                alexaConfiguration.queueLength,
                alexaConfiguration.messageQueueSize);
    }
    catch(boost::interprocess::interprocess_exception &ex)
    {
        if(logger_.isErrorEnable())
        {
            const string message = string("Alexa:: User message queue has not been initialized correctly - ") + ex.what();
            logger_.writeLog(LogType::ERROR_LOG, message);
        }

        return false;
    }

    if (logger_.isInformationEnable())
    {
        const std::string message = std::string("Alexa:: User message queue has been initialized correctly.");
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    return true;
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

void Alexa::entryStateFunction(const string &name) noexcept
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Alexa entry in ##State: " + name;
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void Alexa::exitStateFunction(const string &name) noexcept
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Alexa exit from ##State:" + name;
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void Alexa::initAlexa(const std::string &name) noexcept
{
    (void)name;
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Invoke procedure for alexa.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
    defineInternalState("idle");
}

void Alexa::initIdle(const string &name) noexcept
{
    (void)name;
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Initialized IDLE state.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void Alexa::initLocker(const string &name) noexcept
{
    (void)name;
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Initialized Locker state.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    };

    defineInternalState("closeLocker");
}

void Alexa::initOpenLocker(const string &name) noexcept
{
    (void)name;
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Doors are opened.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    };

    auto response = OpenedDoorResponse();
    const auto data = response.getFrameBytes();
    sendMessage(data);

    handleEvent(transitionTable_.getEvent("ACTIVATE_ALEXA"));
}

void Alexa::initCloseLocker(const string &name) noexcept
{
    (void)name;
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Doors are closed.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    };

    auto response = ClosedDoorResponse();
    const auto data = response.getFrameBytes();
    sendMessage(data);
}

void Alexa::initCoffeeMaker(const string &name) noexcept
{
    (void)name;
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Start coffee maker.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    defineInternalState("latte");
}

void Alexa::initLatte(const string &name) noexcept
{
    (void)name;
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Wow coffee has done!! Send info to user.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    auto response = CoffeeDoneResponse();
    const auto data = response.getFrameBytes();
    sendMessage(data);

    handleEvent(transitionTable_.getEvent("COFFEE_DONE"));
}

void Alexa::sendMessage(const vector<uint8_t> &message)
{
    userQueue_->send(message);
}

void Alexa::visit(MakeCoffeeCommand &command)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received ") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent(transitionTable_.getEvent("MAKE_COFFE"));
}

void Alexa::visit(OpenDoorCommand &command)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received ") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent(transitionTable_.getEvent("OPEN_DOOR"));
}

void Alexa::visit(CloseDoorCommand &command)
{
    if(logger_.isInformationEnable())
    {
        const std::string message = std::string("CommandHandler :: Received ") + command.getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent(transitionTable_.getEvent("CLOSE_DOOR"));
}