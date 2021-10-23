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

   if (Controller.GetBumperPressed(frc::GenericHID::JoystickHand::kLeftHand))
      {
         _RackandPin->Set(ControlMode::PercentOutput, 1);
      }
      else if (Controller.GetBumperPressed(frc::GenericHID::JoystickHand::kRightHand))
      {
         _RackandPin->Set(ControlMode::PercentOutput, -1);
      }
      else
      {
         _RackandPin->Set(0);
      }

}