#pragma once

#include "ctre/Phoenix.h"

#include <frc/PWMTalonFX.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>

#include "Robot.h"

class Drivetrain4810
{
public:

    void setupdrivetrain();
    void rundrivetrain(frc::XboxController &Controller);
	void autoDrive();
	void LimeLightDrive(double driveCmd, double turnCmd);
	void Update_Limelight_Tracking(frc::XboxController &Controller);
    double clamp(double in,double minval,double maxval);
	

private:

  //DriveTrain m_drive;
    WPI_TalonFX * _rghtFront = new WPI_TalonFX(3);
	WPI_TalonFX * _rghtFollower = new WPI_TalonFX(4);

	WPI_TalonFX * _leftFront = new WPI_TalonFX(1);
	WPI_TalonFX * _leftFollower = new WPI_TalonFX(2);

	frc::DifferentialDrive * _diffDrive = new frc::DifferentialDrive(*_leftFront,
			*_rghtFront);

	bool m_LimelightHasTarget;
    double m_LimelightTurnCmd;
    double m_LimelightDriveCmd;

   	int _loops = 0;
	int kSlotIdx = 0;
	/* Talon SRX/ Victor SPX will supported multiple (cascaded) PID loops.
	 * For now we just want the primary one.
	 */
	int kPIDLoopIdx = 0;
	/*
	 * set to zero to skip waiting for confirmation, set to nonzero to wait
	 * and report to DS if action fails.
	 */
	int kTimeoutMs = 30;
	//_talon->ConfigNominalOutputForward(0, kTimeoutMs);
	//_talon->ConfigNominalOutputReverse(0, kTimeoutMs);
	//_talon->ConfigPeakOutputForward(1, kTimeoutMs);
	//_talon->ConfigPeakOutputReverse(-1, kTimeoutMs);

	/* set closed loop gains in slot0 */
	//_talon->Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
	//_talon->Config_kP(kPIDLoopIdx, 0.0, kTimeoutMs);
	//_talon->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	//_talon->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
};