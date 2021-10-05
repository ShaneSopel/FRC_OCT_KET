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
  //frc::Wait(10);
  
  

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

   drive.Update_Limelight_Tracking(DriveController);
   drive.rundrivetrain(DriveController);
   intake.forwardintake(DriveController);
   Sol.Solenoid1(DriveController); 
   shoot.Shooter(OperatorController);
   intake.Conveyor(OperatorController);
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
