#ifndef AHRS_BLACK_BOX_WAICFRAME_H
#define AHRS_BLACK_BOX_WAICFRAME_H

#include <string>
#include <vector>

namespace communication
{
    const uint8_t END_STRING_IN_FRAME = '#';

    enum class FrameType : uint8_t
    {
        RESPONSE = 0x10,
        MEASUREMENT_DATA = 0x20,
        COMMAND = 0x30,
        NOTIFICATION = 0x40
    };

    class Frame
    {
    public:
        Frame(FrameType frameTypeIn, uint16_t dataSizeIn);
        virtual ~Frame();

        virtual std::vector<uint8_t > getFrameBytes() noexcept = 0;
        virtual std::string getName() const noexcept = 0;

        std::vector<uint8_t > getHeader() const noexcept;

        const uint8_t& getPacketNumber() const noexcept;
        void setPacketNumber(uint8_t number);

        const uint16_t& getDataSize() const noexcept;
        void setDataSize(uint16_t dataSize);

        const uint8_t& getSystemVersion() const noexcept;
        const FrameType& getFrameType() const noexcept;

        static const uint8_t HEADER_SIZE = 5;
        static const uint8_t FRAME_TYPE = 1;
        static const uint8_t DATA_SIZE_UINT16_POSITION = 3;
        static const uint8_t RESPONSE_TYPE_POSITION = 5;
        static const uint8_t COMMAND_TYPE_POSITION = 5;
        static const uint8_t INITIAL_DATA_POSITION = 6;

    protected:
        virtual void initializeDataSize() = 0;

        uint8_t systemVersion_;
        FrameType frameType_;
        uint8_t packetNumber_;
        uint16_t dataSize_;
    };
}

#endif
