#ifndef HSM_ALEXASIMULATOR_STATE_H
#define HSM_ALEXASIMULATOR_STATE_H

#include <memory>
#include <string>
#include <functional>
#include <unordered_map>
#include <logger/Logger.h>

#include "Event.h"

namespace hsm
{
    using Callback = std::function<void(const std::string&)>;

    class State
    {
    public:
        State() = delete;
        State(const std::string &name, std::shared_ptr<State> parent = nullptr);

        static void initializeHSMCallbacks(Callback handleEvent, Callback registerInternalState);
        void addTransition(Event event, std::shared_ptr<State> state);
        std::shared_ptr<State> moveToState(Event event);

        virtual void runEntryEvent() = 0;
        virtual void runExitEvent() = 0;
        virtual void runInitEvent() = 0;

        const std::string &getName() const noexcept;
        const uint32_t &getID() const noexcept;
        std::shared_ptr<State> getParent() const noexcept;

        bool operator==(const State &rhs);
        State &operator=(const State &rhs);

    protected:
        static Callback handleEvent_;
        static Callback registerInternalState_;

        utility::Logger &logger_;
    private:
        uint32_t id_;
        std::string name_;
        static bool isCallbackInitialized;

        std::weak_ptr<State> parent_;
        std::unordered_map<Event, std::weak_ptr<State>> stateTable_;
    };
}

#endif