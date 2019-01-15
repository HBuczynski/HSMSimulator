#include "MakeCoffeeBuilder.h"
#include "MakeCoffeeCommand.h"

using namespace std;
using namespace communication;

unique_ptr<Command> MakeCoffeeBuilder::create(const vector<uint8_t> &commandInBytes)
{
    (void)commandInBytes;
    auto command = make_unique<MakeCoffeeCommand>();

    return move(command);
}


