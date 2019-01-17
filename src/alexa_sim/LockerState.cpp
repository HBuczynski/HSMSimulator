#include "LockerState.h"

using namespace hsm;
using namespace std;
using namespace alexa;
using namespace utility;

LockerState::LockerState(const std::string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void LockerState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Alexa entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void LockerState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Alexa exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void LockerState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Initialized Locker state.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    };

    registerInternalState_("closeLocker");
}
