#ifndef OPENED_DOOR_RESPONSE_H
#define OPENED_DOOR_RESPONSE_H

#include "Response.h"

namespace communication
{
    class OpenedDoorResponse final : public Response
    {
    public:
        OpenedDoorResponse();

        virtual std::vector<uint8_t > getFrameBytes() noexcept override;
        virtual std::string getName() const noexcept override;
        virtual void accept(ResponseVisitor& visitor) override;

    private:
        virtual void initializeDataSize() noexcept override;
    };
}

#endif //OPENED_DOOR_RESPONSE_H
