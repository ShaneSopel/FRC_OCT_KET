#pragma once

#include "ctre/Phoenix.h"
#include "Robot.h"
#include <frc/DoubleSolenoid.h>

class Solenoid4810
{
public:

    void Solenoid1(frc::XboxController &Controller);

private:

frc::DoubleSolenoid intakeSolenoid{0,1};
//frc::DoubleSolenoid outtakeSolenoid{2,3};

};