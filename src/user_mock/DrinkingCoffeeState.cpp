#include "DrinkingCoffeeState.h"

using namespace hsm;
using namespace std;
using namespace user;
using namespace utility;

DrinkingCoffeeState::DrinkingCoffeeState(const string &name, shared_ptr<State> parent)
        : State(name, parent)
{}

void DrinkingCoffeeState::runEntryEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User entry in ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void DrinkingCoffeeState::runExitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User exit from ##State: " + getName();
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }
}

void DrinkingCoffeeState::runInitEvent()
{
    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "User started drinking tasty coffee prepared by alexa.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }


    if (logger_.isInformationEnable())
    {
        const string message = string("User:: ") + "I have to go out and close door.";
        logger_.writeLog(LogType::INFORMATION_LOG, message);
    }

    handleEvent_("CLOSE_DOOR");
}
