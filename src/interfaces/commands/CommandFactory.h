#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "Command.h"
#include "CommandBuilder.h"

#include <memory>

namespace communication
{
    class CommandFactory
    {
    public:
        std::unique_ptr<Command> createCommand(const std::vector<uint8_t> &commandInBytes);

    private:
        std::unique_ptr<CommandBuilder> builder_;
    };
}
#endif
