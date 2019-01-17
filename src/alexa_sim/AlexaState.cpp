#include "AlexaState.h"

using namespace hsm;
using namespace std;
using namespace utility;
using namespace alexa;

AlexaState::AlexaState(const std::string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void AlexaState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Alexa entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void AlexaState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Alexa exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void AlexaState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const std::string message = string("Alexa:: ") + "Invoke procedure for alexa.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
    registerInternalState_("idle");
}
