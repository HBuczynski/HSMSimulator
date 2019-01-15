#include "Response.h"

using namespace std;
using namespace communication;

Response::Response(uint8_t dataSizeIn, ResponseType responseTypeIn)
        : Frame(FrameType::RESPONSE, dataSizeIn),
          responseType_(responseTypeIn)
{}

const ResponseType& Response::getResponseType() const noexcept
{
    return responseType_;
}
