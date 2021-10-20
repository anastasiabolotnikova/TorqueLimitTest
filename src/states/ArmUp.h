#pragma once

#include <mc_control/fsm/State.h>

struct ArmUp : mc_control::fsm::State
{

    void configure(const mc_rtc::Configuration & config) override;

    void start(mc_control::fsm::Controller & ctl) override;

    bool run(mc_control::fsm::Controller & ctl) override;

    void teardown(mc_control::fsm::Controller & ctl) override;
private:
    mc_rtc::Configuration config_;
    double postureTaskCompletion_;
    std::map<std::string, std::vector<double>> jointTarget_;
};
