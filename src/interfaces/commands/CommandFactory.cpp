#include "CommandFactory.h"

#include "MakeCoffeeBuilder.h"
#include "OpenDoorBuilder.h"
#include "CloseDoorBuilder.h"
#include "EndConnectionBuilder.h"

#include <stdexcept>

using namespace std;
using namespace communication;

unique_ptr<Command> CommandFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<CommandType>(commandInBytes[Frame::COMMAND_TYPE_POSITION]);

    switch (type)
    {
        case CommandType::MAKE_COFFEE :
            builder_ = make_unique<MakeCoffeeBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::OPEN_DOOR :
            builder_ = make_unique<OpenDoorBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::CLOSE_DOOR :
            builder_ = make_unique<CloseDoorBuilder>();
            return move(builder_->create(commandInBytes));
        case CommandType::END_CONNECTION :
            builder_ = make_unique<EndConnectionBuilder>();
            return move(builder_->create(commandInBytes));
        default:
            throw invalid_argument("Received command does not register in factory.");

    }
}
