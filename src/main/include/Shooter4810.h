#pragma once

#include "ctre/Phoenix.h"
#include "Robot.h"
#include <frc/DoubleSolenoid.h>

class Shooter4810
{
public:

    void Shooter(frc::XboxController &Controller);
    void setupShooter();
    void autoShoot();

private:

    WPI_TalonFX * _shooter = new WPI_TalonFX(6);
	WPI_TalonFX * _shooterFollower = new WPI_TalonFX(10);

};