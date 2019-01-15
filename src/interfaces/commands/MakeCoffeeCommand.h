#ifndef MAKE_COFFEE_COMMAND_H
#define MAKE_COFFEE_COMMAND_H

#include "Command.h"
#include <string>

namespace communication
{
    class MakeCoffeeCommand final : public Command
    {
    public:
        MakeCoffeeCommand();

        virtual std::vector<uint8_t > getFrameBytes() noexcept override;
        virtual std::string getName() const noexcept override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() noexcept override;

    };
}
#endif
