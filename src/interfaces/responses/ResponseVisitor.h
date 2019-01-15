#ifndef RESPONSEVISITOR_H
#define RESPONSEVISITOR_H

#include "OpenedDoorResponse.h"
#include "ClosedDoorResponse.h"
#include "CoffeeDoneResponse.h"

namespace communication
{
    class ResponseVisitor
    {
    public:
        ResponseVisitor() {};
        virtual ~ResponseVisitor() {};

        virtual void visit(OpenedDoorResponse& data) = 0;
        virtual void visit(ClosedDoorResponse& data) = 0;
        virtual void visit(CoffeeDoneResponse& data) = 0;
    };
}

#endif //RESPONSEVISITOR_H
