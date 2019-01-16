#include <logger/Logger.h>

#include "UserMock.h"

using namespace std;
using namespace hsm;
using namespace utility;

int main()
{
    Logger &logger = Logger::getInstance("UserMock");

    InitLogStructure struc;
    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;
    logger.initLogger(struc);

    auto user = make_shared<State>("user");
    auto sleep = make_shared<State>("sleep", user);
    auto makeCoffee = make_shared<State>("makeCoffee", user);
    auto drinkingCoffee = make_shared<State>("drinkingCoffee", user);
    auto goOut = make_shared<State>("goOut", user);
    auto goIn = make_shared<State>("goIn", user);

    TransitionTable transitionTable({
            {sleep,         Event{"MAKE_COFFE"},        makeCoffee},
            {makeCoffee,    Event{"COFFEE_DONE"},       drinkingCoffee},
            {drinkingCoffee,Event{"CLOSE_DOOR"},        goOut},
            {goOut,         Event{"OPEN_DOOR"},         goIn},
    });

/* Define HSM */
    UserMock userMock("User", transitionTable, user);

/* Define states' actions */
    user->addEntryFunction(bind(&UserMock::entryStateFunction, &userMock, std::placeholders::_1));
    sleep->addEntryFunction(bind(&UserMock::entryStateFunction, &userMock, std::placeholders::_1));
    makeCoffee->addEntryFunction(bind(&UserMock::entryStateFunction, &userMock, std::placeholders::_1));
    drinkingCoffee->addEntryFunction(bind(&UserMock::entryStateFunction, &userMock, std::placeholders::_1));
    goOut->addEntryFunction(bind(&UserMock::entryStateFunction, &userMock, std::placeholders::_1));
    goIn->addEntryFunction(bind(&UserMock::entryStateFunction, &userMock, std::placeholders::_1));

    user->addExitFunction(bind(&UserMock::exitStateFunction, &userMock, std::placeholders::_1));
    sleep->addExitFunction(bind(&UserMock::exitStateFunction, &userMock, std::placeholders::_1));
    makeCoffee->addExitFunction(bind(&UserMock::exitStateFunction, &userMock, std::placeholders::_1));
    drinkingCoffee->addExitFunction(bind(&UserMock::exitStateFunction, &userMock, std::placeholders::_1));
    goOut->addExitFunction(bind(&UserMock::exitStateFunction, &userMock, std::placeholders::_1));
    goIn->addExitFunction(bind(&UserMock::exitStateFunction, &userMock, std::placeholders::_1));

    user->addInitFunction(bind(&UserMock::initUser, &userMock, std::placeholders::_1));
    sleep->addInitFunction(bind(&UserMock::initSleeping, &userMock, std::placeholders::_1));
    makeCoffee->addInitFunction(bind(&UserMock::initMakeCoffee, &userMock, std::placeholders::_1));
    drinkingCoffee->addInitFunction(bind(&UserMock::initDrinkCoffee, &userMock, std::placeholders::_1));
    goOut->addInitFunction(bind(&UserMock::initGoOut, &userMock, std::placeholders::_1));
    goIn->addInitFunction(bind(&UserMock::initGoIn, &userMock, std::placeholders::_1));

    cout << transitionTable.showTable() << endl;
    userMock.initialize();

    userMock.run(); cout << endl;

    return 0;
}
