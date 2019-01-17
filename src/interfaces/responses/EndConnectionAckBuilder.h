#ifndef HSMSIMULATOR_ENDCONNECTIONACKBUILDER_H
#define HSMSIMULATOR_ENDCONNECTIONACKBUILDER_H

#include "ResponseBuilder.h"

namespace communication
{
    class EndConnectionAckBuilder final : public ResponseBuilder
    {
    public:
        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif