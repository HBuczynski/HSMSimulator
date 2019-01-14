#include <logger/Logger.h>

using namespace std;
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

    return 0;
}
