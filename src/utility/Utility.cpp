#include <cstdint>
#include "Utility.h"

using namespace utility;

uint32_t Utility::id_ = 0;

const uint32_t &Utility::getStateID() noexcept
{
    return ++id_;
}