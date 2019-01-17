#include <logger/Logger.h>

#include "S1State.h"
#include "S2State.h"
#include "S21State.h"
#include "S11State.h"
#include "TopState.h"
#include "S211State.h"
#include "ExampleHSM.h"

using namespace hsm;
using namespace std;
using namespace example;
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
    shared_ptr<State> top = make_shared<TopState>("top");
    shared_ptr<State> s1 = make_shared<S1State>("s1", top);
    shared_ptr<State> s11 = make_shared<S11State>("s11", s1);
    shared_ptr<State> s2 = make_shared<S2State>("s2", top);
    shared_ptr<State> s21 = make_shared<S21State>("s21", s2);
    shared_ptr<State> s211 = make_shared<S211State>("s211", s21);

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

/* Define HSM */
    ExampleHSM example("exampleHSM", transitionTable, top);
    cout << transitionTable.showTable() << endl;

/* Run Hierarchical State Machine */
    if (logger.isInformationEnable())
    {
        const std::string message = "Main:: Start.";
        logger.writeLog(LogType::INFORMATION_LOG, message);
    }
    cout << "*******************************************************" << endl;
    cout << "\nTo move to the next state write event from 'a' to 'h'" << endl;
    cout << "!!! To exit program write char out of defined range.\n" << endl;
    cout << "*******************************************************" << endl;

    cout << "Start HSM: ";
    example.start();
    cout << endl;
    cout << endl;

/* Testing algorithm */
    string eventKey;
    while(1)
    {
        cout << "Write event: ";
        cin >> eventKey;
        eventKey = toupper(eventKey[0]);

        if (eventKey[0] < 'A' || 'H' < eventKey[0])
        {
            break;
        }
        example.handleEvent(eventKey + "_EVENT");
        cout << endl;
        cout << endl;
    }

/* END */
    return 0;
}