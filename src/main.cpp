#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	imu.reset();
	while(imu.is_calibrating()){
		pros::delay(20);
	}

	autonomousChooserInit();




	pros::Task chassis_task(chassisTask);
	pros::Task lift_task(liftTask);
	pros::Task mogo_task(mogoTask);
	pros::Task intake_task(intakeTask);

	clampPiston(false);
	setMogo(false);
	//pros::lcd::initialize();

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	clampPiston(true);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	while (true){
		_leftReset();
		_rightReset();
		tareLift();
		pros::delay(20);
	}
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
		_leftReset();
		_rightReset();
		tareLift();
		reset();

		progSkills();
		//autonomousChooserExecuteAuto();
		//soloAWP();
		//leftBoth();
		//rightNeutrals();
		//leftNeutrals();


		pros::delay(5000);

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::lcd::initialize();
	while (true) {

		if(master.get_digital(DIGITAL_RIGHT)){
			setChassisMode(1);
			setAccelStep(7);
			//moveForward(24);
			pointTurn(true, 90);
			setChassisMode(0);
		}
		else if (master.get_digital(DIGITAL_DOWN)) {
			setAccelStep(7);
			moveForward(24);
			moveBack(24);
			setChassisMode(0);
		}
		// else{
		// 	setChassisMode(0);
		// 	setLiftMode(0);
		// 	setForkMode(0);
		// }

		setChassisMode(0);
		setLiftMode(0);
		setMogoMode(0);
		setIntakeMode(0);


		pros::delay(20);
	}
}
