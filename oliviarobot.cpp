/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Drive/DifferentialDrive.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <LiveWindow/LiveWindow.h>
#include <Spark.h>
#include <Timer.h>
#include <WPILib.h>

class Robot : public frc::IterativeRobot {
public:
	Robot() {
		m_robotDrive.SetExpiration(0.1);
		m_timer.Start();
	}

	void AutonomousInit() override {
		m_timer.Reset();
		m_timer.Start();
	}

	void AutonomousPeriodic() override {
		// Drive for 2 seconds
		if (m_timer.Get() < 2.0) {
			// Drive forwards half speed
			m_robotDrive.ArcadeDrive(-0.5, 0.0);
		} else {
			// Stop robot
			m_robotDrive.ArcadeDrive(0.0, 0.0);
		}
	}

	void TeleopInit() override {}

	void TeleopPeriodic() override {
		// Drive with arcade style (use right stick)
		m_robotDrive.ArcadeDrive(m_stick.GetY(), m_stick.GetX());

		//REAR MOTOR identification: how to get Y coordinate of joystick
		double joystickJoe = XboxController.GetY(frc::XboxController::JoystickHand::kLeftHand);
		//function sets power of motor to the y coordinate
		mLR.Set(joystickJoe);
		
		double otherjoystickJoe = XboxController.GetY(frc::XboxController::JoystickHand::kLeftHand);
		mRR.Set(otherjoystickJoe);
		
		//FRONT MOTORS
        double joystickJoe = XboxController.GetY(frc::XboxController::JoystickHand::kLeftHand);
        mLF.Set(joystickJoe);
        
        double otherjoystickJoe = XboxController.GetY(frc::XboxController::JoystickHand::kLeftHand);
        mRF.Set(otherjoystickJoe);
		
	}

	void TestPeriodic() override {}

private:
	// Robot drive system
	frc::Spark m_left{0};
	frc::Spark m_right{1};
	frc::DifferentialDrive m_robotDrive{m_left, m_right};
	frc::XboxController XboxController{0};

	frc::Joystick m_stick{0};
	frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();
	frc::Timer m_timer;
	
 //motors
	frc::Spark mLR{0};
	frc::Spark mRR{1};
	frc::Spark mLF{2};
	frc::Spark mRF{3};
	//arm lift
	frc::Spark mT2{4};
	frc::Spark mT1{5};
	//output
	frc::Spark mT3{6};
	frc::Spark mT4{7};
};

START_ROBOT_CLASS(Robot)
