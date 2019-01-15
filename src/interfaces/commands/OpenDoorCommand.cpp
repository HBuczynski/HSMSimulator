#include "OpenDoorCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;
using namespace communication;

OpenDoorCommand::OpenDoorCommand()
        : Command(10, CommandType::OPEN_DOOR)
{}

vector<uint8_t> OpenDoorCommand::getFrameBytes() noexcept
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string OpenDoorCommand::getName() const noexcept
{
    return string("OpenDoorCommand");
}

void OpenDoorCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void OpenDoorCommand::initializeDataSize() noexcept
{
    setDataSize(sizeof(commandType_));
}
