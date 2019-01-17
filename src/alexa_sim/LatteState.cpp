#include "LatteState.h"
#include "AlexaConfig.h"
#include <interfaces/responses/CoffeeDoneResponse.h>

using namespace hsm;
using namespace std;
using namespace alexa;
using namespace utility;

LatteState::LatteState(const std::string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void LatteState::initializeUserQueue(std::shared_ptr<communication::MessageQueueWrapper> queue)
{
    userQueue_ = queue;
}

void LatteState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Alexa entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void LatteState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Alexa exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void LatteState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Wow coffee has done!! Send info to user.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    auto response = communication::CoffeeDoneResponse();
    const auto data = response.getFrameBytes();
    userQueue_->send(data);

    handleEvent_("COFFEE_DONE");
}


