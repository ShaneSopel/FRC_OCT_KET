#pragma once

#include "ctre/Phoenix.h"
#include "Robot.h"
#include <frc/DoubleSolenoid.h>

class RackandPin4810
{
public:

    void RackandPin(frc::XboxController &Controller);
    void setupRackandPin();
    void autoRackandPin();

private:

    WPI_TalonFX * _RackandPin = new WPI_TalonFX(5);
	WPI_TalonFX * _RackandPinFollower = new WPI_TalonFX(1);

};