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
        ~State() = default;

        void addTransition(Event event, std::shared_ptr<State> state);
        std::shared_ptr<State> moveToState(Event event);

        void addInitFunction(Callback init) noexcept;
        void addEntryFunction(Callback entry) noexcept;
        void addExitFunction(Callback exit) noexcept;

        void runEntryEvent() const noexcept;
        void runExitEvent() const noexcept;
        void runInitEvent() const noexcept;

        const std::string& getName() const noexcept;
        const uint32_t &getID() const noexcept;
        std::shared_ptr<State> getParent() const noexcept;

        bool operator==(const State &rhs);
        State &operator=(const State &rhs);

    private:
        std::weak_ptr<State> parent_;
        std::unordered_map<Event, std::weak_ptr<State>> stateTable_;

        Callback initFunction_;
        Callback entryFunction_;
        Callback exitFunction_;

        std::string name_;
        uint32_t id_;

        utility::Logger &logger_;
    };
}

#endif