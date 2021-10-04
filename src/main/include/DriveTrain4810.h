#pragma once

#include "ctre/Phoenix.h"

#include <frc/PWMTalonFX.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>

#include "Robot.h"


//add code to make motors work better.

class Drivetrain4810
{
public:

    void setupdrivetrain();
    void rundrivetrain(frc::XboxController &Controller, double m_LimelightDriveCmd, double m_LimelightTurnCmd, bool m_LimelightHasTarget);
	void autoDrive();
	

private:

  //DriveTrain m_drive;
    WPI_TalonFX * _rghtFront = new WPI_TalonFX(3);
	WPI_TalonFX * _rghtFollower = new WPI_TalonFX(4);

	WPI_TalonFX * _leftFront = new WPI_TalonFX(1);
	WPI_TalonFX * _leftFollower = new WPI_TalonFX(2);

	frc::DifferentialDrive * _diffDrive = new frc::DifferentialDrive(*_leftFront,
			*_rghtFront);

};