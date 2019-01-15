#ifndef CLOSED_DOOR_BUILDER_H
#define CLOSED_DOOR_BUILDER_H

#include "ResponseBuilder.h"

namespace communication
{
    class ClosedDoorBuilder final : public ResponseBuilder
    {
    public:
        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif
