#ifndef CLOSE_BUILDER_h
#define CLOSE_BUILDER_h

#include "CommandBuilder.h"

namespace communication
{
    class CloseDoorBuilder final : public CommandBuilder
    {
    public:
        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}


#endif