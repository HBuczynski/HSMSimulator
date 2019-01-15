#include "CoffeeDoneResponse.h"
#include "ResponseVisitor.h"

using namespace std;
using namespace communication;

CoffeeDoneResponse::CoffeeDoneResponse()
        : Response(10, ResponseType::COFFEE_DONE)
{}

vector<uint8_t> CoffeeDoneResponse::getFrameBytes() noexcept
{
    initializeDataSize();

    vector<uint8_t > frame = getHeader();
    frame.push_back(static_cast<uint8_t>(responseType_));

    return frame;
}

string CoffeeDoneResponse::getName() const noexcept
{
    return string("CoffeeDoneResponse");
}

void CoffeeDoneResponse::accept(ResponseVisitor &visitor)
{
    visitor.visit(*this);
}

void CoffeeDoneResponse::initializeDataSize() noexcept
{
    uint16_t dataSize = sizeof(responseType_);

    setDataSize(dataSize);
}
