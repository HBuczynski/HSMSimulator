#ifndef COFFEEDONE_EBUILDER_H
#define COFFEEDONE_EBUILDER_H

#include "ResponseBuilder.h"

namespace communication
{
    class CoffeeDoneBuilder final : public ResponseBuilder
    {
    public:
        virtual std::unique_ptr<Response> create(const std::vector<uint8_t> &dataInBytes) override;
    };
}

#endif