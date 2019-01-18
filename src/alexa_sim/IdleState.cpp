#include "IdleState.h"

using namespace hsm;
using namespace std;
using namespace alexa;
using namespace utility;

IdleState::IdleState(const string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void IdleState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("Alexa:: ") + "Alexa entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void IdleState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("Alexa:: ") + "Alexa exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void IdleState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("Alexa:: ") + "Initialized IDLE state.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}
