#include "Frame.h"
#include <utility/BytesConverter.h>

using namespace std;
using namespace utility;
using namespace communication;

Frame::Frame(FrameType frameTypeIn, uint16_t dataSizeIn)
    : systemVersion_(1),
      frameType_(frameTypeIn),
      packetNumber_(0),
      dataSize_(dataSizeIn)
{ }

Frame::~Frame()
{ }

vector<uint8_t> Frame::getHeader() const noexcept
{
    vector<uint8_t > header;

    header.push_back(systemVersion_);
    header.push_back(static_cast<uint8_t >(frameType_));
    header.push_back(packetNumber_);
    BytesConverter::appendUINT16toVectorOfUINT8(dataSize_, header);

    return header;
}

const uint8_t& Frame::getPacketNumber() const noexcept
{
    return packetNumber_;
}

void Frame::setPacketNumber(uint8_t number)
{
    packetNumber_ = number;
}

const uint8_t& Frame::getSystemVersion() const noexcept
{
    return systemVersion_;
}

const uint16_t& Frame::getDataSize() const noexcept
{
    return dataSize_;
}

void Frame::setDataSize(uint16_t dataSize)
{
    dataSize_ = dataSize;
}

const FrameType &Frame::getFrameType() const noexcept
{
    return frameType_;
}