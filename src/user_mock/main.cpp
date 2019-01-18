#include <logger/Logger.h>
#include <alexa_sim/AlexaConfig.h>

#include "UserState.h"
#include "GoingInState.h"
#include "SleepingState.h"
#include "GoingOutState.h"
#include "MakingCoffeeState.h"
#include "DrinkingCoffeeState.h"

#include "UserMock.h"

using namespace std;
using namespace hsm;
using namespace user;
using namespace utility;

shared_ptr<communication::MessageQueueWrapper> createMsgQueue(const string &name);

int main()
{
/* Define logger */
    Logger &logger = Logger::getInstance("UserMock");

    InitLogStructure struc;
    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;
    logger.initLogger(struc);

/* Define msg queues */
    alexa::AlexaConfiguration configuration;
    auto userQueue = createMsgQueue(configuration.userMsgQueueName);
    auto alexaQueue = createMsgQueue(configuration.alexaMsgQueueName);

    if(userQueue == nullptr || alexaQueue == nullptr)
    {
        if(logger.isErrorEnable())
        {
            const string message = string("Alexa :: Did not create msg queues.");
            logger.writeLog(LogType::ERROR_LOG, message);
        }
        return 0;
    }

/* Define states */
    auto user = make_shared<UserState>("user");
    auto sleep = make_shared<SleepingState>("sleep", user);
    auto makeCoffee = make_shared<MakingCoffeeState>("makeCoffee", user);
    auto drinkingCoffee = make_shared<DrinkingCoffeeState>("drinkingCoffee", user);
    auto goOut = make_shared<GoingOutState>("goOut", user);
    auto goIn = make_shared<GoingInState>("goIn", user);

/*Define transition table */
    TransitionTable transitionTable({
            {sleep,         Event{"MAKE_COFFE"},        makeCoffee},
            {makeCoffee,    Event{"COFFEE_DONE"},       drinkingCoffee},
            {drinkingCoffee,Event{"CLOSE_DOOR"},        goOut},
            {goOut,         Event{"OPEN_DOOR"},         goIn},
    });
    cout << transitionTable.showTable() << endl;

/* Initialise queue in states. */
    makeCoffee->initializeAlexaQueue(alexaQueue);
    goOut->initializeAlexaQueue(alexaQueue);
    goIn->initializeAlexaQueue(alexaQueue);

/* Define HSM */
    UserMock userMock("User", transitionTable, user);
    userMock.initializeAlexaQueue(alexaQueue);
    userMock.initializeUserQueue(userQueue);

    userMock.run();

    return 0;
}

shared_ptr<communication::MessageQueueWrapper> createMsgQueue(const string &name)
{
    try
    {
        return make_shared<communication::MessageQueueWrapper>(name);
    }
    catch(boost::interprocess::interprocess_exception &ex)
    {
        return nullptr;
    }
}
