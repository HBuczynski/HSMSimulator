#ifndef ALEXASIMULATOR_UTILITY_H
#define ALEXASIMULATOR_UTILITY_H

namespace utility
{
    class Utility final
    {
    public:
        Utility() = default;
        ~Utility() = default;

        static const uint32_t &getStateID() noexcept;

    private:
        static uint32_t id_;
    };
}

#endif