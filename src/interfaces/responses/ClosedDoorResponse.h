#ifndef CLOSED_DOOR_RESPONSE_H
#define CLOSED_DOOR_RESPONSE_H

#include "Response.h"

namespace communication
{
    class ClosedDoorResponse final : public Response
    {
    public:
        ClosedDoorResponse();

        virtual std::vector<uint8_t > getFrameBytes() noexcept override;
        virtual std::string getName() const noexcept override;
        virtual void accept(ResponseVisitor& visitor) override;

    private:
        virtual void initializeDataSize() noexcept override;

    };
}

#endif