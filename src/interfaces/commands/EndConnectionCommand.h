#ifndef HSMSIMULATOR_ENDCONNECTIONCOMMAND_H
#define HSMSIMULATOR_ENDCONNECTIONCOMMAND_H

#include "Command.h"
#include <string>

namespace communication
{
    class EndConnectionCommand final : public Command
    {
    public:
        EndConnectionCommand();

        virtual std::vector<uint8_t > getFrameBytes() noexcept override;
        virtual std::string getName() const noexcept override;
        virtual void accept(CommandVisitor& visitor) override;

    private:
        virtual void initializeDataSize() noexcept override;

    };
}

#endif