#include "MakeCoffeeCommand.h"
#include "CommandVisitor.h"

using namespace std;
using namespace communication;

MakeCoffeeCommand::MakeCoffeeCommand()
    : Command(10, CommandType::MAKE_COFFEE)
{}

vector<uint8_t> MakeCoffeeCommand::getFrameBytes() noexcept
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(commandType_));

    return frame;
}

string MakeCoffeeCommand::getName() const noexcept
{
    return string("MakeCoffeeCommand");
}

void MakeCoffeeCommand::accept(CommandVisitor &visitor)
{
    visitor.visit(*this);
}

void MakeCoffeeCommand::initializeDataSize() noexcept
{
    uint16_t dataSize = sizeof(commandType_);
    setDataSize(dataSize);
}
