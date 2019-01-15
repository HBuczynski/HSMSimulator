#include "OpenedDoorResponse.h"
#include "ResponseVisitor.h"

using namespace std;
using namespace communication;

OpenedDoorResponse::OpenedDoorResponse()
    : Response(10, ResponseType::DOOR_OPENED)
{}

vector<uint8_t> OpenedDoorResponse::getFrameBytes() noexcept
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));

    return frame;
}

string OpenedDoorResponse::getName() const noexcept
{
    return string("OpenedDoorResponse");
}

void OpenedDoorResponse::initializeDataSize() noexcept
{
    uint16_t dataSize = sizeof(responseType_);

    setDataSize(dataSize);
}

void OpenedDoorResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}
