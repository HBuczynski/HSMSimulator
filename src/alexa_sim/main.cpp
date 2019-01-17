#include <message_queue_wrapper/MessageQueueWrapper.h>
#include <logger/Logger.h>

#include "AlexaConfig.h"
#include "IdleState.h"
#include "LatteState.h"
#include "AlexaState.h"
#include "LockerState.h"
#include "OpenLockerState.h"
#include "CloseLockerState.h"
#include "CoffeeMakerState.h"

#include "Alexa.h"

using namespace std;
using namespace hsm;
using namespace alexa;
using namespace utility;

shared_ptr<communication::MessageQueueWrapper> createUserMsgQueue();
shared_ptr<communication::MessageQueueWrapper> createAlexaMsgQueue();

int main()
{
/* Define logger */
    Logger &logger = Logger::getInstance("Alexa");

    InitLogStructure struc;
    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;
    logger.initLogger(struc);

/* Define msg queues */
    auto userQueue = createUserMsgQueue();
    auto alexaQueue = createAlexaMsgQueue();

    if(userQueue.get() == nullptr || alexaQueue.get() == nullptr)
    {
        if(logger.isErrorEnable())
        {
            const string message = string("Alexa :: Did not create msg queues.");
            logger.writeLog(LogType::ERROR_LOG, message);
        }
        return 0;
    }

/* Define states */
    auto alexa = make_shared<AlexaState>("alexa");
    auto idle = make_shared<IdleState>("idle", alexa);
    auto locker = make_shared<LockerState>("locker", alexa);
    auto openLocker = make_shared<OpenLockerState>("openLocker", locker);
    auto closeLocker = make_shared<CloseLockerState>("closeLocker", locker);
    auto coffeeMaker = make_shared<CoffeeMakerState>("coffeeMaker", alexa);
    auto latte = make_shared<LatteState>("latte", coffeeMaker);

/*Define transition table */
    TransitionTable transitionTable({
            {idle,         Event{"MAKE_COFFE"},        coffeeMaker},
            {coffeeMaker,   Event{"COFFEE_DONE"},       idle},
            {alexa,         Event{"CLOSE_DOOR"},        closeLocker},
            {alexa,         Event{"OPEN_DOOR"},         openLocker},
            {locker,        Event{"ACTIVATE_ALEXA"},    idle},
    });
    transitionTable.addNotBindState(latte);
    cout << transitionTable.showTable() << endl;

/* Initialise queue in states. */
    closeLocker->initializeUserQueue(userQueue);
    openLocker->initializeUserQueue(userQueue);
    latte->initializeUserQueue(userQueue);

/* Define HSM */
    Alexa alexaHSM("Alexa", transitionTable, alexa);

/* Run Hierarchical State Machine */
    alexaHSM.initializeAlexaQueue(alexaQueue);
    alexaHSM.initializeUserQueue(userQueue);
    alexaHSM.run();

    return 0;
}

shared_ptr<communication::MessageQueueWrapper> createUserMsgQueue()
{
    shared_ptr<communication::MessageQueueWrapper> userQueue = nullptr;
    AlexaConfiguration configuration;
    try
    {
        userQueue = make_shared<communication::MessageQueueWrapper>(configuration.userMsgQueueName,
                                                                    configuration.queueLength,
                                                                    configuration.messageQueueSize);
    }
    catch(boost::interprocess::interprocess_exception &ex)
    {
        return userQueue;
    }

    return userQueue;
}

shared_ptr<communication::MessageQueueWrapper> createAlexaMsgQueue()
{
    shared_ptr<communication::MessageQueueWrapper> alexaQueue = nullptr;
    AlexaConfiguration configuration;
    try
    {
        alexaQueue = make_shared<communication::MessageQueueWrapper>(configuration.alexaMsgQueueName,
                                                                     configuration.queueLength,
                                                                     configuration.messageQueueSize);
    }
    catch(boost::interprocess::interprocess_exception &ex)
    {
        return alexaQueue;
    }

    return alexaQueue;
}
