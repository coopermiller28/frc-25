// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <wpi/sendable/SendableRegistry.h>


class Robot : public frc::TimedRobot {
  frc::PWMSparkMax leftFrontMotor{0};
  frc::PWMSparkMax leftBackMotor{3};
  frc::MotorControllerGroup leftMotors{leftFrontMotor, leftBackMotor}; // Groups left motors

  frc::PWMSparkMax rightFrontMotor{1};
  frc::PWMSparkMax rightBackMotor{4};
  frc::MotorControllerGroup rightMotors{rightFrontMotor, rightBackMotor}; // Groups right motors

  frc::DifferentialDrive robotDrive{leftMotors, rightMotors};
    [&](double output) { leftMotors.Set(output); },
    [&](double output) { rightMotors.Set(output); }};
  frc::Joystick m_stick{0};

 public:
  Robot() {
    wpi::SendableRegistry::AddChild(&robotDrive, &leftMotors);
    wpi::SendableRegistry::AddChild(&robotDrive, &rightMotors);


    rightMotors.SetInverted(true); // Inverts right side motors
  }

  void TeleopPeriodic() override {
    robotDrive.ArcadeDrive(-m_stick.GetY(), -m_stick.GetX());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
