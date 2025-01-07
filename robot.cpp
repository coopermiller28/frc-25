// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with arcade steering.
 */
class Robot : public frc::TimedRobot {
  frc::PWMSparkMax leftFrontMotor{0};
  frc::PWMSparkMax leftBackMotor{3};
  frc::MotorControllerGroup leftMotors{leftFrontMotor, leftBackMotor};

  frc::PWMSparkMax rightFrontMotor{1};
  frc::PWMSparkMax rightBackMotor{4};
  frc::MotorControllerGroup rightMotors{rightFrontMotor, rightBackMotor};

  frc::DifferentialDrive robotDrive{leftMotors, rightMotors};
    [&](double output) { leftMotors.Set(output); },
    [&](double output) { rightMotors.Set(output); }};
  frc::Joystick m_stick{0};

 public:
  Robot() {
    wpi::SendableRegistry::AddChild(&m_robotDrive, &m_leftMotors);
    wpi::SendableRegistry::AddChild(&m_robotDrive, &m_rightMotors);

    // We need to invert one side of the drivetrain so that positive voltages
    // result in both sides moving forward. Depending on how your robot's
    // gearbox is constructed, you might have to invert the left side instead.
    m_rightMotors.SetInverted(true);
  }

  void TeleopPeriodic() override {
    // Drive with arcade style
    m_robotDrive.ArcadeDrive(-m_stick.GetY(), -m_stick.GetX());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
