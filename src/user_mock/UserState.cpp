#include "UserState.h"

using namespace hsm;
using namespace std;
using namespace user;
using namespace utility;

UserState::UserState(const std::string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void UserState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("User:: ") + "User entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UserState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("User:: ") + "User exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void UserState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("User:: ") + "Invoked procedure for - " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
    registerInternalState_("sleep");
}
