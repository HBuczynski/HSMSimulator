#ifndef COMMAND_VISITOR_H
#define COMMAND_VISITOR_H

#include "MakeCoffeeCommand.h"
#include "OpenDoorCommand.h"
#include "CloseDoorCommand.h"
#include "EndConnectionCommand.h"

namespace communication
{
    class CommandVisitor
    {
    public:
        CommandVisitor(){};
        virtual ~CommandVisitor(){};

        virtual void visit(MakeCoffeeCommand& command) = 0;
        virtual void visit(OpenDoorCommand& command) = 0;
        virtual void visit(CloseDoorCommand& command) = 0;
        virtual void visit(EndConnectionCommand& command) = 0;
    };
}
#endif
