#include "CloseDoorBuilder.h"
#include "CloseDoorCommand.h"

using namespace std;
using namespace communication;

unique_ptr<Command> CloseDoorBuilder::create(const vector<uint8_t> &commandInBytes)
{
    (void)commandInBytes;
    auto command = make_unique<CloseDoorCommand>();

    return move(command);
}
