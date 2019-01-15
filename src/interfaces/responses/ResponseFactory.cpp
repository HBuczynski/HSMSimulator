#include "ResponseFactory.h"
#include "OpenedDoorBuilder.h"
#include "ClosedDoorBuilder.h"
#include "CoffeeDoneBuilder.h"

using namespace std;
using namespace communication;

unique_ptr<Response> ResponseFactory::createCommand(const vector<uint8_t> &commandInBytes)
{
    const auto type = static_cast<ResponseType >(commandInBytes[Frame::RESPONSE_TYPE_POSITION]);

    switch (type)
    {
        case ResponseType::DOOR_OPENED:
            builder_ = make_unique<OpenedDoorBuilder>();
            return move(builder_->create(commandInBytes));
        case ResponseType::DOOR_CLOSED:
            builder_ = make_unique<ClosedDoorBuilder>();
            return move(builder_->create(commandInBytes));
        case ResponseType::COFFEE_DONE:
            builder_ = make_unique<CoffeeDoneBuilder>();
            return move(builder_->create(commandInBytes));
        default:
            throw invalid_argument("Received command does not register in factory.");
    }
}