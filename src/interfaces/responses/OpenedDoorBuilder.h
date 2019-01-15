#ifndef OPENED_DOORBUILDER_H
#define OPENED_DOORBUILDER_H

#include "ResponseBuilder.h"

namespace communication
{
    class OpenedDoorBuilder final : public ResponseBuilder
    {
    public:
        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}
#endif
