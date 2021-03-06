#ifndef COMMANDBUILDER_H
#define COMMANDBUILDER_H

#include "Command.h"

#include <memory>
#include <vector>

namespace communication
{
    class CommandBuilder
    {
    public:
        virtual std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) = 0;

    };
}
#endif
