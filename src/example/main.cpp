#include <logger/Logger.h>

#include "ExampleHSM.h"

using namespace hsm;
using namespace std;
using namespace utility;

int main()
{
/* Initialize logger */
    Logger &logger = Logger::getInstance("Example");

    InitLogStructure struc;
    struc.debugLog = true;
    struc.errroLog = true;
    struc.informationLog = true;
    struc.warningLog = true;
    struc.writeLogsInSeparetFiles = true;
    struc.writeOnConsole = true;
    logger.initLogger(struc);

    if (logger.isInformationEnable())
    {
        const std::string message = "Main:: States initialization.";
        logger.writeLog(LogType::INFORMATION_LOG, message);
    }

/* Define states */
    auto top = make_shared<State>("top");
    auto s1 = make_shared<State>("s1", top);
    auto s11 = make_shared<State>("s11", s1);
    auto s2 = make_shared<State>("s2", top);
    auto s21 = make_shared<State>("s21", s2);
    auto s211 = make_shared<State>("s211", s21);

    if (logger.isInformationEnable())
    {
        const std::string message = "Main:: Building transition table.";
        logger.writeLog(LogType::INFORMATION_LOG, message);
    }

/* Define transition table */
    TransitionTable transitionTable({
                                        {top,   Event{"E_EVENT"}, s211},
                                        {s1,    Event{"A_EVENT"}, s1},
                                        {s1,    Event{"B_EVENT"}, s11},
                                        {s1,    Event{"C_EVENT"}, s2},
                                        {s1,    Event{"D_EVENT"}, top},
                                        {s1,    Event{"F_EVENT"}, s211},
                                        {s11,   Event{"G_EVENT"}, s211},
                                        {s11,   Event{"H_EVENT"}, s11},
                                        {s2,    Event{"C_EVENT"}, s1},
                                        {s2,    Event{"F_EVENT"}, s11},
                                        {s21,   Event{"B_EVENT"}, s211},
                                        {s21,   Event{"H_EVENT"}, s21},
                                        {s211,  Event{"D_EVENT"}, s21},
                                        {s211,  Event{"G_EVENT"}, top}
    });

    if (logger.isInformationEnable())
    {
        const std::string message = "Main:: Definition of events.";
        logger.writeLog(LogType::INFORMATION_LOG, message);
    }

/* Define HSM */
    ExampleHSM example("exampleHSM", transitionTable, top);

/* Define states' actions */
    top->addEntryFunction(bind(&ExampleHSM::entryStateFunction, &example, std::placeholders::_1));
    s1->addEntryFunction(bind(&ExampleHSM::entryStateFunction, &example, std::placeholders::_1));
    s11->addEntryFunction(bind(&ExampleHSM::entryStateFunction, &example, std::placeholders::_1));
    s2->addEntryFunction(bind(&ExampleHSM::entryStateFunction, &example, std::placeholders::_1));
    s21->addEntryFunction(bind(&ExampleHSM::entryStateFunction, &example, std::placeholders::_1));
    s211->addEntryFunction(bind(&ExampleHSM::entryStateFunction, &example, std::placeholders::_1));

    top->addExitFunction(bind(&ExampleHSM::exitStateFunction, &example, std::placeholders::_1));
    s1->addExitFunction(bind(&ExampleHSM::exitStateFunction, &example, std::placeholders::_1));
    s11->addExitFunction(bind(&ExampleHSM::exitStateFunction, &example, std::placeholders::_1));
    s2->addExitFunction(bind(&ExampleHSM::exitStateFunction, &example, std::placeholders::_1));
    s21->addExitFunction(bind(&ExampleHSM::exitStateFunction, &example, std::placeholders::_1));
    s211->addExitFunction(bind(&ExampleHSM::exitStateFunction, &example, std::placeholders::_1));

    top->addInitFunction(bind(&ExampleHSM::initTop, &example, std::placeholders::_1));
    s1->addInitFunction(bind(&ExampleHSM::inits1, &example, std::placeholders::_1));
    s11->addInitFunction(bind(&ExampleHSM::inits11, &example, std::placeholders::_1));
    s2->addInitFunction(bind(&ExampleHSM::inits2, &example, std::placeholders::_1));
    s21->addInitFunction(bind(&ExampleHSM::inits21, &example, std::placeholders::_1));
    s211->addInitFunction(bind(&ExampleHSM::init211, &example, std::placeholders::_1));

    cout << transitionTable.showTable() << endl;

/* Run Hierarchical State Machine */
    example.start(); cout << endl;

    example.handleEvent(transitionTable.getEvent("A_EVENT")); cout << endl;
    example.handleEvent(transitionTable.getEvent("B_EVENT")); cout << endl;
    example.handleEvent(transitionTable.getEvent("D_EVENT")); cout << endl;
    example.handleEvent(transitionTable.getEvent("E_EVENT")); cout << endl;

/* END */

    return 0;
}
