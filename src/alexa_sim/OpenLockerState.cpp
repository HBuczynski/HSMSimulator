#include "OpenLockerState.h"
#include "AlexaConfig.h"
#include <interfaces/responses/OpenedDoorResponse.h>

using namespace hsm;
using namespace std;
using namespace alexa;
using namespace utility;

OpenLockerState::OpenLockerState(const string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void OpenLockerState::initializeUserQueue(shared_ptr<communication::MessageQueueWrapper> queue)
{
    userQueue_ = queue;
}

void OpenLockerState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("Alexa:: ") + "Alexa entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void OpenLockerState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("Alexa:: ") + "Alexa exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void OpenLockerState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("Alexa:: ") + "Doors are opened.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    };

    auto response = communication::OpenedDoorResponse();
    const auto data = response.getFrameBytes();
    userQueue_->send(data);

    handleEvent_("ACTIVATE_ALEXA");
}


