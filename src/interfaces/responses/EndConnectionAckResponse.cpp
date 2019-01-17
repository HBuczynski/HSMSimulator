#include "EndConnectionAckResponse.h"
#include "ResponseVisitor.h"

using namespace std;
using namespace communication;

EndConnectionAckResponse::EndConnectionAckResponse()
        : Response(10, ResponseType::END_CONNECTION_ACK)
{}

vector<uint8_t> EndConnectionAckResponse::getFrameBytes() noexcept
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));

    return frame;
}

string EndConnectionAckResponse::getName() const noexcept
{
    return string("EndConnectionAckResponse");
}

void EndConnectionAckResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}

void EndConnectionAckResponse::initializeDataSize() noexcept
{
    uint16_t dataSize = sizeof(responseType_);

    setDataSize(dataSize);
}
