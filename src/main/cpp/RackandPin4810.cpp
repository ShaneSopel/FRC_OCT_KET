#include "RackandPin4810.h"
#include <frc/smartdashboard/SmartDashboard.h>


void RackandPin4810::setupRackandPin()
{
   
   _RackandPinFollower->Follow(*_RackandPin);
   _RackandPinFollower->SetInverted(true);

/* Set Motion Magic gains in slot0 - see documentation */
    _RackandPin->SelectProfileSlot(0, 0);


    /* Set acceleration and vcruise velocity - see documentation */
    _RackandPin->ConfigMotionCruiseVelocity(1500, 10);
    _RackandPin->ConfigMotionAcceleration(1500, 10);

    /* Zero the sensor */
    _RackandPin->SetSelectedSensorPosition(0, 0, 10);



}

void RackandPin4810::autoRackandPin()
{
  _RackandPin->Set(1*1);
  frc::Wait(3);
  _RackandPin->Set(0);
  
  // change set value  ( 0-100) 1*.55   55%
}

void RackandPin4810::RackandPin(frc::XboxController &Controller)
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
	_RackandPin->Set(ControlMode::PercentOutput, Controller.GetY(frc::GenericHID::JoystickHand::kLeftHand) * -1); /* 40 Amps in either direction */
	
		
   if (Controller.GetBButtonPressed())
   {
       _RackandPin->Set(0);
   }
 

}