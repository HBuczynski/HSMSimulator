#include "EndConnectionAckBuilder.h"
#include "EndConnectionAckResponse.h"

using namespace std;
using namespace communication;

unique_ptr<Response> EndConnectionAckBuilder::create(const vector<uint8_t> &dataInBytes)
{
    (void)dataInBytes;
    auto command = make_unique<EndConnectionAckResponse>();

    return move(command);
}
