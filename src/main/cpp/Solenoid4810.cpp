
#include "Solenoid4810.h"

void Solenoid4810::Solenoid1(frc::XboxController &Controller)
{
       //intake solenoid reverse
   if(Controller.GetBumperPressed(frc::GenericHID::JoystickHand::kLeftHand))
   {
       // solenoid
    intakeSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
   }

   //intake solenoid Forward
   if(Controller.GetBumperPressed(frc::GenericHID::JoystickHand::kRightHand))
   {
       // solenoid
    intakeSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
   }
}