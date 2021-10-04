#include "Intake4810.h"


void Intake4810::setupintake()
{
   
}

void Intake4810::forwardintake(frc::XboxController &DriveController)
{
  if(DriveController.GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand))
   {
        _Intake->Set(ControlMode::PercentOutput, 50);
   }
  else if(DriveController.GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand))
   {
        _Intake->Set(ControlMode::PercentOutput, -50);
   }
    else   
        _Intake->Set(ControlMode::PercentOutput, 0);
    }

void Intake4810::Conveyor(frc::XboxController &OperatorController)
{
    if (OperatorController.GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand))
    {
        _Conveyor->Set(ControlMode::PercentOutput, 50);
        _FeederWheel->Set(ControlMode::PercentOutput, -50);
    }
    else if (OperatorController.GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand))
    {
        _Conveyor->Set(ControlMode::PercentOutput, -50);
        _FeederWheel->Set(ControlMode::PercentOutput, 50);
    }
    else
    {
        _Conveyor->Set(ControlMode::PercentOutput, 0);
        _FeederWheel->Set(ControlMode::PercentOutput, 0);   
    }
}
void Intake4810::autoconveyor()
{
         _Conveyor->Set(ControlMode::PercentOutput, -50);
        _FeederWheel->Set(ControlMode::PercentOutput, 50);
        // may need to change
}



/*void Intake4810::forwardintake(frc::XboxController &Controller)
{
   
    //hatch intake
  if(Controller.GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand))
   {
        _Conveyor->Set(ControlMode::PercentOutput, 50);
        _FeederWheel->Set(ControlMode::PercentOutput, -50);
        _Intake->Set(ControlMode::PercentOutput, 50);
   }
  else if(Controller.GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand))
   {
        _Conveyor->Set(ControlMode::PercentOutput, -50);
        _FeederWheel->Set(ControlMode::PercentOutput, 50);
        _Intake->Set(ControlMode::PercentOutput, -50);
   }
    else   
    {
        _Conveyor->Set(ControlMode::PercentOutput, 0);
        _FeederWheel->Set(ControlMode::PercentOutput, 0);
        _Intake->Set(ControlMode::PercentOutput, 0);
    }
  
}
*/