#ifndef OPEN_DOOR_COMMAND_H
#define OPEN_DOOR_COMMAND_H

#include "Command.h"

namespace communication
{
    class OpenDoorCommand final: public Command
    {
    public:
        OpenDoorCommand();

        virtual std::vector<uint8_t > getFrameBytes() noexcept override;
        virtual std::string getName() const noexcept override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() noexcept override;
    };
}


#endif
