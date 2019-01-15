#include "OpenedDoorBuilder.h"
#include "OpenedDoorResponse.h"

using namespace std;
using namespace communication;

unique_ptr<Response> OpenedDoorBuilder::create(const vector<uint8_t> &dataInBytes)
{
    (void)dataInBytes;
    auto command = make_unique<OpenedDoorResponse>();

    return move(command);
}
