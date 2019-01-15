#ifndef MAKE_COFFEE_BUILDER_H
#define MAKE_COFFEE_BUILDER_H

#include "CommandBuilder.h"

namespace communication
{
    class MakeCoffeeBuilder final : public CommandBuilder
    {
    public:
        std::unique_ptr<Command> create(const std::vector<uint8_t> &commandInBytes) override;
    };
}

#endif