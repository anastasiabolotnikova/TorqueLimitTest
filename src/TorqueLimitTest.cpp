#include "TorqueLimitTest.h"
#include <mc_rtc/gui/plot.h>

using Color = mc_rtc::gui::Color;

TorqueLimitTest::TorqueLimitTest(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config)
: mc_control::fsm::Controller(rm, dt, config)
{
  if(robot().name()!="onedof"){
    mc_rtc::log::error_and_throw<std::runtime_error>("TorqueLimitTest controller requires OneDoF as main robot");
  }
  if(robot().q()[0].size()!=0){
    mc_rtc::log::error_and_throw<std::runtime_error>("TorqueLimitTest controller requires OneDoF as main robot");
  }
  config_.load(config);
  mc_rtc::log::success("TorqueLimitTest init done");
}

bool TorqueLimitTest::run()
{
  t_+=solver().dt();
  return mc_control::fsm::Controller::run();
}

void TorqueLimitTest::reset(const mc_control::ControllerResetData & reset_data)
{
  mc_control::fsm::Controller::reset(reset_data);

  std::string jN = "joint";
  if(robot().hasJoint(jN)){
    unsigned int jI = robot().jointIndexByName(jN);
    gui()->addPlot("Torque (Nm) green, Speed (m/s) blue",
                mc_rtc::gui::plot::X("Time (s)", [this]() { return t_; }),
                mc_rtc::gui::plot::Y(jN, [this, jI]() { return robot().mbc().jointTorque[jI][0]; }, Color::Green),
                mc_rtc::gui::plot::Y(jN, [this, jI]() { return robot().mbc().alpha[jI][0]; }, Color::Blue),
                mc_rtc::gui::plot::Y("UL", [this, jI]() { return robot().tu()[jI][0]; }, Color::Red),
                mc_rtc::gui::plot::Y("LL", [this, jI]() { return robot().tl()[jI][0]; }, Color::Red)
              );
  }else{
    mc_rtc::log::error_and_throw<std::runtime_error>("Robot {} does not have joint named {}", robot().name(), jN);
  }

  auto getQ = [this]() -> const std::vector<double> &
  {
    static std::vector<double> q(robot().refJointOrder().size());
    auto & mbc = robot().mbc();
    const auto & rjo = robot().refJointOrder();
    int i=0;
    for(const auto & jn : rjo){
      for(auto & j : mbc.q[robot().jointIndexByName(jn)]){
        q[i] = j;
      }
      i++;
    }
    return q;
  };

  auto getV = [this]() -> const std::vector<double> &
  {
    static std::vector<double> v(robot().refJointOrder().size());
    auto & mbc = robot().mbc();
    const auto & rjo = robot().refJointOrder();
    int i=0;
    for(const auto & jn : rjo){
      for(auto & j : mbc.alpha[robot().jointIndexByName(jn)]){
        v[i] = j;
      }
      i++;
    }
    return v;
  };

  auto getA = [this]() -> const std::vector<double> &
  {
    static std::vector<double> a(robot().refJointOrder().size());
    auto & mbc = robot().mbc();
    const auto & rjo = robot().refJointOrder();
    int i=0;
    for(const auto & jn : rjo){
      for(auto & j : mbc.alphaD[robot().jointIndexByName(jn)]){
        a[i] = j;
      }
      i++;
    }
    return a;
  };

  auto getT = [this]() -> const std::vector<double> &
  {
    static std::vector<double> t(robot().refJointOrder().size());
    auto & mbc = robot().mbc();
    const auto & rjo = robot().refJointOrder();
    int i=0;
    for(const auto & jn : rjo){
      for(auto & j : mbc.jointTorque[robot().jointIndexByName(jn)]){
        t[i] = j;
      }
      i++;
    }
    return t;
  };

  auto getP = [this]() -> const std::vector<double> &
  {
    auto postureObjective = getPostureTask("onedof")->posture();
    static std::vector<double> p(robot().refJointOrder().size());
    auto & mbc = robot().mbc();
    const auto & rjo = robot().refJointOrder();
    int i=0;
    for(const auto & jn : rjo){
      auto ji = robot().jointIndexByName(jn);
      p[i] = postureObjective[ji][0];
      i++;
    }
    return p;
  };

  logger().addLogEntry(
    "Robot_Joints", [getQ]() -> const std::vector<double> & { return getQ(); });

  logger().addLogEntry(
    "Robot_Speed", [getV]() -> const std::vector<double> & { return getV(); });

  logger().addLogEntry(
    "Robot_Acceleration", [getA]() -> const std::vector<double> & { return getA(); });

  logger().addLogEntry(
    "Robot_Torque", [getT]() -> const std::vector<double> & { return getT(); });

  logger().addLogEntry(
    "Robot_Target", [getP]() -> const std::vector<double> & { return getP(); });
}
