#include "TorqueLimitTest_Initial.h"

#include "../TorqueLimitTest.h"

void TorqueLimitTest_Initial::configure(const mc_rtc::Configuration & config)
{
}

void TorqueLimitTest_Initial::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<TorqueLimitTest &>(ctl_);
}

bool TorqueLimitTest_Initial::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<TorqueLimitTest &>(ctl_);
  output("OK");
  return true;
}

void TorqueLimitTest_Initial::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<TorqueLimitTest &>(ctl_);
}

EXPORT_SINGLE_STATE("TorqueLimitTest_Initial", TorqueLimitTest_Initial)
