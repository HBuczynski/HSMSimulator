#include "CoffeeMakerState.h"

using namespace hsm;
using namespace std;
using namespace utility;
using namespace alexa;

CoffeeMakerState::CoffeeMakerState(const string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void CoffeeMakerState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("Alexa:: ") + "Alexa entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CoffeeMakerState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("Alexa:: ") + "Alexa exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void CoffeeMakerState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("Alexa:: ") + "Start coffee maker.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    registerInternalState_("latte");
}
