#include "ArmUp.h"

#include "../TorqueLimitTest.h"

void ArmUp::configure(const mc_rtc::Configuration & config)
{
  config_.load(config);
}

void ArmUp::start(mc_control::fsm::Controller & ctl_)
{
  if(!config_.has("jointTarget")){
    mc_rtc::log::error_and_throw<std::runtime_error>("ArmUp | jointTarget config entry missing");
  }
  config_("jointTarget", jointTarget_);

  ctl_.getPostureTask("onedof")->target(jointTarget_);
}

bool ArmUp::run(mc_control::fsm::Controller & ctl_)
{
  return false;
}

void ArmUp::teardown(mc_control::fsm::Controller & ctl_)
{
}

EXPORT_SINGLE_STATE("ArmUp", ArmUp)
