#include <logger/Logger.h>

#include "Alexa.h"

using namespace std;
using namespace hsm;
using namespace alexa;
using namespace utility;

int main()
{
    Logger &logger = Logger::getInstance("Alexa");

    InitLogStructure struc;
    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;
    logger.initLogger(struc);

    auto alexa = make_shared<State>("alexa");
    auto idle = make_shared<State>("idle", alexa);
    auto locker = make_shared<State>("locker", alexa);
    auto openLocker = make_shared<State>("openLocker", locker);
    auto closeLocker = make_shared<State>("closeLocker", locker);
    auto coffeeMaker = make_shared<State>("coffeeMaker", alexa);
    auto latte = make_shared<State>("latte", coffeeMaker);

    TransitionTable transitionTable({
            {idle,         Event{"MAKE_COFFE"},        coffeeMaker},
            {coffeeMaker,   Event{"COFFEE_DONE"},       idle},
            {alexa,         Event{"CLOSE_DOOR"},        closeLocker},
            {alexa,         Event{"OPEN_DOOR"},         openLocker},
            {locker,        Event{"ACTIVATE_ALEXA"},    idle},

    });

    transitionTable.addNotBindState(latte);

/* Define HSM */
    Alexa alexaHSM("Alexa", transitionTable, alexa);

/* Define states' actions */
    alexa->addEntryFunction(bind(&Alexa::entryStateFunction, &alexaHSM, std::placeholders::_1));
    idle->addEntryFunction(bind(&Alexa::entryStateFunction, &alexaHSM, std::placeholders::_1));
    locker->addEntryFunction(bind(&Alexa::entryStateFunction, &alexaHSM, std::placeholders::_1));
    openLocker->addEntryFunction(bind(&Alexa::entryStateFunction, &alexaHSM, std::placeholders::_1));
    closeLocker->addEntryFunction(bind(&Alexa::entryStateFunction, &alexaHSM, std::placeholders::_1));
    coffeeMaker->addEntryFunction(bind(&Alexa::entryStateFunction, &alexaHSM, std::placeholders::_1));
    latte->addEntryFunction(bind(&Alexa::entryStateFunction, &alexaHSM, std::placeholders::_1));

    alexa->addExitFunction(bind(&Alexa::exitStateFunction, &alexaHSM, std::placeholders::_1));
    idle->addExitFunction(bind(&Alexa::exitStateFunction, &alexaHSM, std::placeholders::_1));
    locker->addExitFunction(bind(&Alexa::exitStateFunction, &alexaHSM, std::placeholders::_1));
    openLocker->addExitFunction(bind(&Alexa::exitStateFunction, &alexaHSM, std::placeholders::_1));
    closeLocker->addExitFunction(bind(&Alexa::exitStateFunction, &alexaHSM, std::placeholders::_1));
    coffeeMaker->addExitFunction(bind(&Alexa::exitStateFunction, &alexaHSM, std::placeholders::_1));
    latte->addExitFunction(bind(&Alexa::exitStateFunction, &alexaHSM, std::placeholders::_1));

    alexa->addInitFunction(bind(&Alexa::initAlexa, &alexaHSM, std::placeholders::_1));
    idle->addInitFunction(bind(&Alexa::initIdle, &alexaHSM, std::placeholders::_1));
    locker->addInitFunction(bind(&Alexa::initLocker, &alexaHSM, std::placeholders::_1));
    openLocker->addInitFunction(bind(&Alexa::initOpenLocker, &alexaHSM, std::placeholders::_1));
    closeLocker->addInitFunction(bind(&Alexa::initCloseLocker, &alexaHSM, std::placeholders::_1));
    coffeeMaker->addInitFunction(bind(&Alexa::initCoffeeMaker, &alexaHSM, std::placeholders::_1));
    latte->addInitFunction(bind(&Alexa::initLatte, &alexaHSM, std::placeholders::_1));

    cout << transitionTable.showTable() << endl;

/* Run Hierarchical State Machine */
    alexaHSM.initialize();
    alexaHSM.run();

    return 0;
}
