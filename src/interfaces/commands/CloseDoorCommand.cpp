#include "CloseDoorCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

CloseDoorCommand::CloseDoorCommand()
        : Command(10, CommandType::CLOSE_DOOR)
{}

vector<uint8_t> CloseDoorCommand::getFrameBytes() noexcept
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string CloseDoorCommand::getName() const noexcept
{
    return string("CloseDoorCommand");
}

void CloseDoorCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void CloseDoorCommand::initializeDataSize() noexcept
{
    setDataSize(sizeof(commandType_));
}
