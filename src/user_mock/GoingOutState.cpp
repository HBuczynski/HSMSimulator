#include "GoingOutState.h"
#include <../alexa_sim/AlexaConfig.h>
#include <interfaces/commands/CloseDoorCommand.h>

using namespace hsm;
using namespace std;
using namespace user;
using namespace utility;

GoingOutState::GoingOutState(const std::string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void GoingOutState::initializeAlexaQueue(std::shared_ptr<communication::MessageQueueWrapper> queue)
{
    alexaQueue_ = queue;
}

void GoingOutState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("User:: ") + "User entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void GoingOutState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("User:: ") + "User exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void GoingOutState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("User:: ") + "User go out from house.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    auto command = communication::CloseDoorCommand();
    const auto data = command.getFrameBytes();
    alexaQueue_->send(data);
}


