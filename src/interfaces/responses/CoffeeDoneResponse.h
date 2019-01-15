#ifndef AHRS_CURRENTSTATERESPONSE_H
#define AHRS_CURRENTSTATERESPONSE_H

#include "Response.h"

namespace communication
{
    class CoffeeDoneResponse final : public Response
    {
    public:
        CoffeeDoneResponse();

        virtual std::vector<uint8_t > getFrameBytes() noexcept override;
        virtual std::string getName() const noexcept override;
        virtual void accept(ResponseVisitor& visitor) override;

    private:
        virtual void initializeDataSize() noexcept override;
    };
}


#endif