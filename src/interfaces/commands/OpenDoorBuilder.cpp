#include "OpenDoorBuilder.h"
#include "OpenDoorCommand.h"

using namespace std;
using namespace communication;

unique_ptr<Command> OpenDoorBuilder::create(const vector<uint8_t> &commandInBytes)
{
    (void)commandInBytes;

    auto command = make_unique<OpenDoorCommand>();

    return move(command);
}
