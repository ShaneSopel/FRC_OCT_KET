#include "DriveTrain4810.h"

void Drivetrain4810::setupdrivetrain()
{
      /* factory default values */
		_rghtFront->ConfigFactoryDefault();
		_rghtFollower->ConfigFactoryDefault();
		_leftFront->ConfigFactoryDefault();
		_leftFollower->ConfigFactoryDefault();

		/* set up followers */
		_rghtFollower->Follow(*_rghtFront);
		_leftFollower->Follow(*_leftFront);

		/* [3] flip values so robot moves forward when stick-forward/LEDs-green */
		_rghtFront->SetInverted(TalonFXInvertType::Clockwise);
		_rghtFollower->SetInverted(TalonFXInvertType::FollowMaster);
		_leftFront->SetInverted(TalonFXInvertType::CounterClockwise);
		_leftFollower->SetInverted(TalonFXInvertType::FollowMaster);

        _diffDrive->SetRightSideInverted(false);
}

void Drivetrain4810::rundrivetrain(frc::XboxController &Controller, double m_LimelightDriveCmd, double m_LimelightTurnCmd, bool m_LimelightHasTarget)
{

	  bool do_limelight = Controller.GetAButton();
     if (do_limelight)
     {
        if (m_LimelightHasTarget)
        {
          _diffDrive->ArcadeDrive(m_LimelightDriveCmd,m_LimelightTurnCmd);
        }
        else
        {
          _diffDrive->ArcadeDrive(0.0,0.0);
        }
     }

	double forw = +1 * Controller.GetY(frc::GenericHID::JoystickHand::kLeftHand); /* positive is forward */
	double turn = -1 * Controller.GetX(frc::GenericHID::JoystickHand::kRightHand); /* positive is right */

	if (fabs(forw) < 0.10)
		forw = 0;
	if (fabs(turn) < 0.10)
		turn = 0;

    _diffDrive->ArcadeDrive(forw, turn,true);
}

void Drivetrain4810::autoDrive()
{
	_diffDrive->ArcadeDrive(+1*.99, 0);
	frc::Wait(.1);
	_diffDrive->ArcadeDrive(+1*.9, 0);
	frc::Wait(.1);
	_diffDrive->ArcadeDrive(+1*.9, 0);
	frc::Wait(.1);
	_diffDrive->ArcadeDrive(+1*.9, 0);
	frc::Wait(.2);
	/*_diffDrive->ArcadeDrive(+1*.9, 0);
	frc::Wait(.1);
	_diffDrive->ArcadeDrive(+1*.9, 0);
	frc::Wait(.1); */


	_diffDrive->ArcadeDrive(0, 0);
	frc::Wait(7);
	// change set value 
}