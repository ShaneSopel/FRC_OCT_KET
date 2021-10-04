// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/PWMTalonFX.h>
#include <frc/SpeedControllerGroup.h>

#include "ctre/Phoenix.h"

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <frc/GenericHID.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>

#include <frc/Compressor.h>


class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;


  void Update_Limelight_Tracking();


 private:

  frc::XboxController DriveController{0};
  frc::XboxController OperatorController{1};
  frc::Compressor *c = new frc::Compressor(0);

  WPI_TalonFX * _shooterMaster = new WPI_TalonFX(11);
  WPI_TalonFX * _shooterSlave = new WPI_TalonFX(12);

  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  bool m_LimelightHasTarget;
  double m_LimelightTurnCmd;
  double m_LimelightDriveCmd;
};
