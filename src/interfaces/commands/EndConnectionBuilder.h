#ifndef HSMSIMULATOR_ENDCONNECTIONBUILDER_H
#define HSMSIMULATOR_ENDCONNECTIONBUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class EndConnectionBuilder final : public CommandBuilder
    {
    public:
        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif