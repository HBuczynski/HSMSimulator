#include "ClosedDoorResponse.h"
#include "ResponseVisitor.h"

using namespace std;
using namespace communication;

ClosedDoorResponse::ClosedDoorResponse()
    : Response(10, ResponseType::DOOR_CLOSED)
{}

vector<uint8_t> ClosedDoorResponse::getFrameBytes() noexcept
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));

    return frame;
}

void ClosedDoorResponse::initializeDataSize() noexcept
{
    uint16_t dataSize = sizeof(responseType_);

    setDataSize(dataSize);
}

string ClosedDoorResponse::getName() const noexcept
{
    return string("ClosedDoorResponse");
}

void ClosedDoorResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}
