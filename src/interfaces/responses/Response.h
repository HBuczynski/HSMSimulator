#ifndef RESPONSE_H
#define RESPONSE_H

#include <interfaces/frame/Frame.h>

namespace communication
{
    class ResponseVisitor;

    enum ResponseType : uint8_t
    {
        COFFEE_DONE = 0x01,
        DOOR_CLOSED = 0x02,
        DOOR_OPENED = 0x03
    };

    class Response : public Frame
    {
    public:
        Response(uint8_t dataSizeIn, ResponseType commandTypeIn);
        virtual ~Response() = default;

        virtual std::vector<uint8_t > getFrameBytes() noexcept = 0;
        virtual std::string getName() const noexcept = 0;
        virtual void accept(ResponseVisitor& visitor) = 0;

        const ResponseType& getResponseType() const noexcept ;

    protected:
        virtual void initializeDataSize() noexcept = 0;

        ResponseType responseType_;

    };
}

#endif
