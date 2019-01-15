#include "ClosedDoorBuilder.h"
#include "ClosedDoorResponse.h"

using namespace std;
using namespace communication;

unique_ptr<Response> ClosedDoorBuilder::create(const vector<uint8_t> &dataInBytes)
{
    (void)dataInBytes;

    auto command = make_unique<ClosedDoorResponse>();
    return move(command);
}
