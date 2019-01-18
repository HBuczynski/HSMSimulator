#include "CloseLockerState.h"
#include <interfaces/responses/ClosedDoorResponse.h>

using namespace hsm;
using namespace std;
using namespace alexa;
using namespace utility;

CloseLockerState::CloseLockerState(const string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void CloseLockerState::initializeUserQueue(shared_ptr<communication::MessageQueueWrapper> queue)
{
    userQueue_ = queue;
}

void CloseLockerState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("Alexa:: ") + "Alexa entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CloseLockerState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("Alexa:: ") + "Alexa exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CloseLockerState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("Alexa:: ") + "Doors are closed.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    };

    auto response = communication::ClosedDoorResponse();
    const auto data = response.getFrameBytes();
    userQueue_->send(data);
}
