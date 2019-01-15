#include "CoffeeDoneBuilder.h"
#include "CoffeeDoneResponse.h"

using namespace std;
using namespace communication;

unique_ptr<Response> CoffeeDoneBuilder::create(const vector<uint8_t> &dataInBytes)
{
    (void)dataInBytes;
    auto command = make_unique<CoffeeDoneResponse>();

    return move(command);
}