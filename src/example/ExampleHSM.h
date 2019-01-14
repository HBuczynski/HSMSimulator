#ifndef ALEXASIMULATOR_ALEXAHSM_H
#define ALEXASIMULATOR_ALEXAHSM_H

#include <hsm/HSM.h>

class ExampleHSM final : public hsm::HSM
{
public:
    ExampleHSM(const std::string& name, const hsm::TransitionTable &transitionTable, std::shared_ptr<hsm::State> rootState);

    void entryStateFunction(const std::string &name) noexcept;
    void exitStateFunction(const std::string &name) noexcept;

    void initTop(const std::string &name) noexcept;
    void inits1(const std::string &name) noexcept;
    void inits11(const std::string &name) noexcept;
    void inits2(const std::string &name) noexcept;
    void inits21(const std::string &name) noexcept;
    void init211(const std::string &name) noexcept;
};

#endif