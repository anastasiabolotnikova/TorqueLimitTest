#pragma once

#include <mc_control/mc_controller.h>
#include <mc_control/fsm/Controller.h>

#include "api.h"

struct TorqueLimitTest_DLLAPI TorqueLimitTest : public mc_control::fsm::Controller
{
    TorqueLimitTest(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config);

    bool run() override;

    void reset(const mc_control::ControllerResetData & reset_data) override;
private:
    mc_rtc::Configuration config_;
    // Time for plot
    double t_ = 0.0;
};
