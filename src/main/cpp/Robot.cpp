// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

//helloworld

#include "DriveTrain4810.h"
#include "Intake4810.h"
#include "Solenoid4810.h"
#include "Shooter4810.h"

#include <frc/Timer.h>

double clamp(double in,double minval,double maxval)
{
  if (in > maxval) return maxval;
  if (in < minval) return minval;
  return in;
}


Drivetrain4810 drive;
Intake4810 intake;
Solenoid4810 Sol;
Shooter4810 shoot;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
   
   drive.setupdrivetrain();
   shoot.setupShooter();

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

// Sequence may need to change (seconds & power)
void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  drive.setupdrivetrain();
  shoot.setupShooter(); 
  drive.autoDrive();
  frc::Wait(10);
  
  

  /* intake.autoconveyor();
  frc::Wait(1);
  shoot.autoShoot();
  frc::Wait(1);
  intake.autoconveyor();
  frc::Wait(1);
  shoot.autoShoot();
  frc::Wait(1);
  intake.autoconveyor();
  frc::Wait(1);
  shoot.autoShoot();  
  //frc::Wait(1);
  //drive.autoDrive();
  //frc::Wait(5);*/

  }
}

void Robot::TeleopInit() {

    c->Enabled();
    c->GetClosedLoopControl();
    c->GetCompressorNotConnectedFault();
    c->SetClosedLoopControl(true);
  
}

void Robot::TeleopPeriodic() 
{

   Update_Limelight_Tracking();

   drive.rundrivetrain(DriveController, m_LimelightDriveCmd, m_LimelightTurnCmd, m_LimelightHasTarget);
   intake.forwardintake(DriveController);
   Sol.Solenoid1(DriveController); 
   shoot.Shooter(OperatorController);
   intake.Conveyor(OperatorController);
}

void Robot::Update_Limelight_Tracking()
{
    // Proportional Steering Constant:
  // If your robot doesn't turn fast enough toward the target, make this number bigger
  // If your robot oscillates (swings back and forth past the target) make this smaller
  const double STEER_K = 0.05;

  // Proportional Drive constant: bigger = faster drive
  const double DRIVE_K = 0.26;

  // Area of the target when your robot has reached the goal
  const double DESIRED_TARGET_AREA = 13.0;
  const double MAX_DRIVE = 0.65;
  const double MAX_STEER = 1.0f;

  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  double tx = table->GetNumber("tx",0.0);
  double ty = table->GetNumber("ty",0.0);
  double ta = table->GetNumber("ta",0.0);
  double tv = table->GetNumber("tv",0.0);

  if (tv < 1.0)
  {
        m_LimelightHasTarget = false;
        m_LimelightDriveCmd = 0.0;
        m_LimelightTurnCmd = 0.0;
  }
  else
  {
        m_LimelightHasTarget = true;

        // Proportional steering
        m_LimelightTurnCmd = tx*STEER_K;
        m_LimelightTurnCmd = clamp(m_LimelightTurnCmd,-MAX_STEER,MAX_STEER);

        // drive forward until the target area reaches our desired area
        m_LimelightDriveCmd = (DESIRED_TARGET_AREA - ta) * DRIVE_K;
        m_LimelightDriveCmd = clamp(m_LimelightDriveCmd,-MAX_DRIVE,MAX_DRIVE);
  }
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
