#ifndef RESPONSEFACTORY_H
#define RESPONSEFACTORY_H

#include "ResponseBuilder.h"

namespace communication
{
    class ResponseFactory
    {
    public:
        std::unique_ptr<Response> createCommand(const std::vector<uint8_t> &commandInBytes);

    private:
        std::unique_ptr<ResponseBuilder> builder_;
    };
}

#endif //RESPONSEFACTORY_H
