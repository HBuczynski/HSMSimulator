#ifndef COMMAND_H
#define COMMAND_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class CommandVisitor;

    enum CommandType : uint8_t
    {
        MAKE_COFFEE = 0x01,
        CLOSE_DOOR = 0x02,
        OPEN_DOOR = 0x03
    };

    class Command : public Frame
    {
    public:
        Command(uint8_t dataSizeIn, CommandType commandTypeIn);
        virtual ~Command() = default;

        virtual std::vector<uint8_t > getFrameBytes() noexcept = 0;
        virtual std::string getName() const noexcept = 0;
        virtual void accept(CommandVisitor& visitor) = 0;

        const CommandType& getCommandType() const noexcept;

    protected:
        virtual void initializeDataSize() noexcept = 0;

        CommandType commandType_;
    };
}
#endif
