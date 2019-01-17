#ifndef HSMSIMULATOR_ENDCONNECTIONACKRESPONSE_H
#define HSMSIMULATOR_ENDCONNECTIONACKRESPONSE_H

#include "Response.h"

namespace communication
{
    class EndConnectionAckResponse final : public Response
    {
    public:
        EndConnectionAckResponse();

        virtual std::vector<uint8_t > getFrameBytes() noexcept override;
        virtual std::string getName() const noexcept override;
        virtual void accept(ResponseVisitor& visitor) override;

    private:
        virtual void initializeDataSize() noexcept override;
    };
}

#endif