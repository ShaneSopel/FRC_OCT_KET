#pragma once

#include "ctre/Phoenix.h"
#include "Robot.h"
#include <frc/SpeedControllerGroup.h>
#include <frc/DoubleSolenoid.h>

class Intake4810
{
public:

    void setupintake();
    void forwardintake(frc::XboxController &Controller);
    void reverseIntake(frc::XboxController &Controller);
    void Conveyor(frc::XboxController &OperatorController);

    void autoconveyor();

private:

// Intake Motors
WPI_TalonSRX *_Conveyor = new WPI_TalonSRX(9);
WPI_TalonSRX *_FeederWheel = new WPI_TalonSRX(10);
WPI_TalonSRX *_Intake = new WPI_TalonSRX(8);

frc::DoubleSolenoid intakeSolenoid{3,4};

};