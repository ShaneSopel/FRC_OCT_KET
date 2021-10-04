#include "Shooter4810.h"
#include <frc/smartdashboard/SmartDashboard.h>


void Shooter4810::setupShooter()
{
   
   _shooterFollower->Follow(*_shooter);
   _shooterFollower->SetInverted(true);

/* Set Motion Magic gains in slot0 - see documentation */
    _shooter->SelectProfileSlot(0, 0);


    /* Set acceleration and vcruise velocity - see documentation */
    _shooter->ConfigMotionCruiseVelocity(1500, 10);
    _shooter->ConfigMotionAcceleration(1500, 10);

    /* Zero the sensor */
    _shooter->SetSelectedSensorPosition(0, 0, 10);



}

void Shooter4810::autoShoot()
{
  _shooter->Set(1*1);
  frc::Wait(3);
  _shooter->Set(0);
  
  // change set value  ( 0-100) 1*.55   55%
}

void Shooter4810::Shooter(frc::XboxController &Controller)
{

    
   //    if(Controller.GetAButtonPressed())
   
//double direction = 1;
//       double velocityRPM = 10000;
//        double Vel = 1;

//        _shooter->Config_kF(0, 0.3, 10);
//        _shooter->Config_kP(0, 0.1, 10);
//        _shooter->Config_kI(0, 0.0, 10);
//        _shooter->Config_kD(0, 0.0, 10);

        // shooter
//        _shooter->Set(TalonFXControlMode::PercentOutput , 1);       


  /* Position mode - button just pressed */
	_shooter->Set(ControlMode::PercentOutput, Controller.GetY(frc::GenericHID::JoystickHand::kLeftHand) * -1); /* 40 Amps in either direction */
	
		
   if (Controller.GetBButtonPressed())
   {
       _shooter->Set(0);
   }
 

}