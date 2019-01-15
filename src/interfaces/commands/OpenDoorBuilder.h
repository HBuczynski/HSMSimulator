#ifndef OPEN_DOOR_BUILDER_H
#define OPEN_DOOR_BUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class OpenDoorBuilder final : public CommandBuilder
    {
    public:
        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}


#endif