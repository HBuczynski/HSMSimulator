#ifndef CLOSE_COMMAND_H
#define CLOSE_COMMAND_H

#include "Command.h"

namespace communication
{
    class CloseDoorCommand final : public Command
    {
    public:
        CloseDoorCommand();

        virtual std::vector<uint8_t > getFrameBytes() noexcept override;
        virtual std::string getName() const noexcept override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() noexcept override;
    };
}


#endif
