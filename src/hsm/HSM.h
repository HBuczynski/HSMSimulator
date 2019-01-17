#ifndef ALEXASIMULATOR_HSMINTERFACE_H
#define ALEXASIMULATOR_HSMINTERFACE_H

#include "TransitionTable.h"

namespace hsm
{
    class HSM
    {
    public:
        HSM() = delete;
        HSM(const std::string& name, const TransitionTable &transitionTable, std::shared_ptr<State> rootState);
        virtual ~HSM() = default;

        void start();
        void handleEvent(const std::string &eventName) noexcept;

    private:
        void registerInternalState(const std::string &name) noexcept;
        void stateTransition(std::shared_ptr<State> state) noexcept;

        void tracePathToTarget();

        uint16_t leastCommonAncestor(std::shared_ptr<State> state);
        void exitToLCA(uint16_t toLCA);

        const std::string NAME;
        TransitionTable transitionTable_;

        std::shared_ptr<State> nextState_;
        std::shared_ptr<State> sourceState_;
        std::shared_ptr<State> currentState_;
        std::shared_ptr<State> rootState_;
    };
}

#endif