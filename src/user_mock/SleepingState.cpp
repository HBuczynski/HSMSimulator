#include "SleepingState.h"

using namespace hsm;
using namespace std;
using namespace user;
using namespace utility;

SleepingState::SleepingState(const string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void SleepingState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void SleepingState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void SleepingState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User is still sleeping.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent_("MAKE_COFFE");
}
