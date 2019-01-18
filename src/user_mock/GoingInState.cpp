#include "GoingInState.h"
#include <interfaces/commands/EndConnectionCommand.h>

using namespace hsm;
using namespace std;
using namespace user;
using namespace utility;

GoingInState::GoingInState(const string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void GoingInState::initializeAlexaQueue(shared_ptr<communication::MessageQueueWrapper> queue)
{
    alexaQueue_ = queue;
}

void GoingInState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void GoingInState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void GoingInState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User again is in a house.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "It is the end of the story. Shutting down alexa.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    auto command = communication::EndConnectionCommand();
    auto const data = command.getFrameBytes();
    alexaQueue_->send(data);
}
