#include "MakingCoffeeState.h"
#include <interfaces/commands/MakeCoffeeCommand.h>

using namespace hsm;
using namespace std;
using namespace user;
using namespace utility;

MakingCoffeeState::MakingCoffeeState(const string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void MakingCoffeeState::initializeAlexaQueue(shared_ptr<communication::MessageQueueWrapper> queue)
{
    alexaQueue_ = queue;
}

void MakingCoffeeState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void MakingCoffeeState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void MakingCoffeeState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User waked up.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    auto command = communication::MakeCoffeeCommand();
    const auto data = command.getFrameBytes();
    alexaQueue_->send(data);

    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User sent request for making coffee.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}



