#include "DriveTrain4810.h"

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

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

        _diffDrive->SetRightSideInverted(false);\
		
		_leftFront->ConfigOpenloopRamp(0.2);
		_leftFollower->ConfigOpenloopRamp(0.2);

		_rghtFront->ConfigOpenloopRamp(0.2);
		_rghtFollower->ConfigOpenloopRamp(0.2);
}

void Drivetrain4810::rundrivetrain(frc::XboxController &Controller)
{
	double forw = +1 * Controller.GetY(frc::GenericHID::JoystickHand::kLeftHand); /* positive is forward */
	double turn = -1 * Controller.GetX(frc::GenericHID::JoystickHand::kRightHand); /* positive is right */

int currentJoystick = forw;
    int lastJoystick = 0;

    if (forw == 1)
        lastJoystick = 1;

    if (forw == -1)
        lastJoystick = -1;

    if (lastJoystick > currentJoystick)
    {
        if (currentJoystick == 0)
        {
            {
                _leftFront->Set(ControlMode::PercentOutput, -1);
                _rghtFront->Set(ControlMode::PercentOutput, -1);
            }
            frc::Wait(0.25);
            {
                _leftFront->Set(ControlMode::PercentOutput, 0);
                _rghtFront->Set(ControlMode::PercentOutput, 0);
                lastJoystick = 0;
            }
        }
    }

    if (lastJoystick < currentJoystick)
    {
        if (currentJoystick == 0)
        {
            {
                _leftFront->Set(ControlMode::PercentOutput, 1);
                _rghtFront->Set(ControlMode::PercentOutput, 1);
            }
            frc::Wait(0.25);
            {
                _leftFront->Set(ControlMode::PercentOutput, 0);
                _rghtFront->Set(ControlMode::PercentOutput, 0);
                lastJoystick = 0;
            }
        }
    }

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

double Drivetrain4810::clamp(double in,double minval,double maxval)
{
  if (in > maxval) return maxval;
  if (in < minval) return minval;
  return in;
}

void Drivetrain4810::Update_Limelight_Tracking(frc::XboxController &Controller)
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

  std::shared_ptr<NetworkTable> table = NetworkTable::GetTable("limelight");
  float tx = table->GetNumber("tx", 0.0);
  double ty = table->GetNumber("ty",0.0);
  double ta = table->GetNumber("ta",0.0);
  double tv = table->GetNumber("tv",0.0);

  bool do_limelight = Controller.GetAButtonPressed();

  if (do_limelight == true)
  {
	if (tx < 1.0)
	{
			m_LimelightHasTarget = false;
			m_LimelightDriveCmd = 0.0;
			m_LimelightTurnCmd = 0.0;
	}
	else if (tx > 1.0)
	{
			m_LimelightHasTarget = true;

			// Proportional steering
			m_LimelightTurnCmd = tx*STEER_K;
			m_LimelightTurnCmd = clamp(m_LimelightTurnCmd,-MAX_STEER,MAX_STEER);

			// drive forward until the target area reaches our desired area
			m_LimelightDriveCmd = (DESIRED_TARGET_AREA - ta) * DRIVE_K;
			m_LimelightDriveCmd = clamp(m_LimelightDriveCmd,-MAX_DRIVE,MAX_DRIVE);
	}
			_diffDrive->ArcadeDrive(m_LimelightDriveCmd, m_LimelightTurnCmd);
  }

}