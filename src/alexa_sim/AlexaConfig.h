#ifndef HSMSIMULATOR_ALEXACONFIG_H
#define HSMSIMULATOR_ALEXACONFIG_H

#include <string>

namespace alexa
{
    struct AlexaConfiguration
    {
        const std::string alexaMsgQueueName = "Alexa";
        const std::string userMsgQueueName = "User";

        uint16_t queueLength = 200;
        uint16_t messageQueueSize = 200;
    };
}

#endif //HSMSIMULATOR_ALEXACONFIG_H
