#include "Command.h"

using namespace std;
using namespace communication;

Command::Command(uint8_t dataSizeIn, CommandType commandTypeIn)
    : Frame(FrameType::COMMAND, dataSizeIn),
      commandType_(commandTypeIn)
{}

const CommandType& Command::getCommandType() const noexcept
{
    return commandType_;
}
