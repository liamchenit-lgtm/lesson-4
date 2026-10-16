#include "main.h"
#include "pros/adi.hpp"
#include "pros/rtos.hpp"
#include "pros/motors.hpp"
#include "pros/vision.hpp"

using namespace pros;

// Every time "LEFT_WHEELS_PORT" is used, it will be replaced with the value 1.
#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 2
#define ARM_PORT 3
#define CLAW_PORT 4
#define IMU_PORT 7

// Drivetrian definitions
Motor left_wheels (LEFT_WHEELS_PORT);
Motor right_wheels (RIGHT_WHEELS_PORT);

/**
 * This function is called when the center button on the V5 LCD is pressed.
 * It can be used to perform actions such as starting a program or displaying
 * a message.
 */
void on_center_button() {
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}





















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

// ======================== Time Based =======================

void autonomous() {
	// Starting the motors
	left_wheels.move_velocity(50);
	right_wheels.move_velocity(50);

	// Adding a delay
	pros::delay(3000);            // 3000 ms = 3 seconds

	// Stopping motors 
	left_wheels.move_velocity(0);
	right_wheels.move_velocity(0);

	// 1) How do you turn the robot left and right?
	// 2) How do you make the robot travel a specific distance?
	// 3) What could be the reason that the robot doesn’t drive perfectly straight?
	
	//	Make an algorithm that drives the robot in a T shape:
	//	1. Drive until 1 meter away from the end wall
	//	2. Turn right and drive for 2m
	//	3. Reverses 2m
	//	4. Turns 180 degrees and drives 2m again
	//	5. Reverses 2m
	//	6. Turns right and drives back to its start position 
	
}



// ==========================================================================================================================================================
// ===================================================================== Motor Encoding =====================================================================
// ==========================================================================================================================================================

// Move relative can be done with ticks.

// Alternatively, you can use wheel diameter and gear ratio to calculate
// the number of ticks to move a certain distance.

// 1800 ticks/rev with 36:1 gears
// 900 ticks/rev with 18:1 gears
// 300 ticks/rev with 6:1 gears

// TASK: Finish the code below so it completes the same T shape as above, but using motor encoding.

/*============================ Delete  
 void autonomous() {
	const int timeout = 1500; // 2 seconds timeout for each step
	int elapsed_time = 0;

	// ------------------  1) drive forward  ------------------
	// reset encoders
	left_wheels.tare_position();
	right_wheels.tare_position();

	// Degrees, speed
	left_wheels.move_absolute(4500, 100);
	right_wheels.move_absolute(4500, 100);
 	
	// Delay until previous step is finished
	while ( elapsed_time < timeout && ( fabs(left_wheels.get_position() - left_wheels.get_target_position()) > 10 ||
    	fabs(right_wheels.get_position() - right_wheels.get_target_position()) > 10) ){
		pros::lcd::print(0, "Working on 1!");
    	pros::delay(10);
		elapsed_time += 10; // Increment elapsed time by 10 ms
	}

	pros::lcd::print(0, "done 1!");
	elapsed_time = 0;


	// ------------------  2) Turn right and go forward  ------------------
	// reset encoders
	left_wheels.tare_position();
	right_wheels.tare_position();

	// Degrees, speed
	left_wheels.move_relative(700, 100);
	right_wheels.move_relative(-700, 100);

 	while ( elapsed_time < timeout && ( fabs(left_wheels.get_position() - left_wheels.get_target_position()) > 10 ||
       fabs(right_wheels.get_position() - right_wheels.get_target_position()) > 10) ){
		pros::lcd::print(0, "Working on 2a!");
	    pros::delay(10);
		elapsed_time += 10; // Increment elapsed time by 10 ms
	}
	pros::lcd::print(0, "done 2a!");
	elapsed_time = 0;


	// reset encoders
	left_wheels.tare_position();
	right_wheels.tare_position();

	// Degrees, speed
	left_wheels.move_relative(1500, 100);
	right_wheels.move_relative(1500, 100);

	while ( elapsed_time < timeout && ( fabs(left_wheels.get_position() - left_wheels.get_target_position()) > 10 ||
		fabs(right_wheels.get_position() - right_wheels.get_target_position()) > 10) ){
		pros::lcd::print(0, "Working on 2b!");
		pros::delay(10);
		elapsed_time += 10; // Increment elapsed time by 10 ms
	}
	pros::lcd::print(0, "done 2b!");
	elapsed_time = 0;
	
 }
 ============================ Delete */




// ==========================================================================================================================================================
// ===================================================================== IMU & Distance =====================================================================
// ==========================================================================================================================================================

// Task: Finish the code below so it completes the same T shape as above, but using IMU and distance sensor.

/* ============================ Delete 
void autonomous() {

	// IMU and Distance Sensor definitions
	IMU imu (IMU_PORT); // IMU on port 1
	Distance dist_sensor (2); // Distance sensor on port 2

	left_wheels.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    right_wheels.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

	const int timeout = 1500; // Timeout in milliseconds
	int elapsed_time = 0; // Initialize elapsed time

    // Calibrate IMU
    imu.reset();

    while (imu.is_calibrating()) {
		pros::delay(10);
	}

    // 1) ------------------------------------- Drive until 60cm from wall -------------------------------------
    // units are in mm
    while (dist_sensor.get() > 600) {  
        left_wheels.move(75);
        right_wheels.move(75);
        pros::delay(10);
    }

    // brake quickly stops motors, but does not stop further movement
    left_wheels.brake();
    right_wheels.brake();


	// 2) ------------------------------------- Turn 90° right -------------------------------------
    //Find the rotation goal, which is 90° more than the current
	// Spot turing where one wheel is powered forward and the other is powered backward
	// Alternatively a swerve turn only has one wheel powered
    double initial_heading = imu.get_heading();
    double target_heading = initial_heading + 75;
	// Why is the target heading lower than 90°?

    while (imu.get_heading() < target_heading - 2) {
		pros::delay(10);
        left_wheels.move(50);
        right_wheels.move(-50);
		pros::lcd::print(0, "Current Reading: %f", imu.get_heading());
    }

    left_wheels.brake();
    right_wheels.brake();

	// Move forward
	left_wheels.tare_position();
	right_wheels.tare_position();

	left_wheels.move_relative(1500, 100);
	right_wheels.move_relative(1500, 100);

	while ( elapsed_time < timeout && ( fabs(left_wheels.get_position() - left_wheels.get_target_position()) > 10 ||
		fabs(right_wheels.get_position() - right_wheels.get_target_position()) > 10) ){
		pros::delay(10);
		elapsed_time += 10; // Increment elapsed time by 10 ms
	}
	elapsed_time = 0;

}

// Now try using the IMU to drive straight!

========================================= DELETE */










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

	// Practice: Try using the code above to define the right wheels

	// Claw and arm definitions
	Motor claw (CLAW_PORT);
	Motor arm (ARM_PORT); 
	arm.set_brake_mode(MOTOR_BRAKE_HOLD);

	// Controller definitions
	Controller master (CONTROLLER_MASTER);

	while (true) {
		// Finish the code so that the left stick controls the drive! (Tank drive)
		int power = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X );

		//  Now try setting the left and right wheels to move based on the left and right analog sticks (Arcade Drive)
		// Think about the advantages and disadvantages of both

		// What input from the controller will control the turning?
		int left = power + turn;
		int right = power - turn;
		
		left_wheels.move(left);
		right_wheels.move(right);
			

		// Set the arm to move based on the left bumpers
		if (master.get_digital(DIGITAL_L1)) {
			arm.move_velocity(100);
		}
		else if (master.get_digital(DIGITAL_L2)) {
			arm.move_velocity(-100);
		}
		else {
			arm.move_velocity(0);
		}

		// Set the claw to move based on the right bumpers
		// Fill out the rest of the code using the example above for the claw!
		if (master.get_digital(DIGITAL_R1 )) {
			claw.move_velocity(100);
		}
		else if (master.get_digital(DIGITAL_R2 )) {
			claw.move_velocity(-100);
		}
		else {
			claw.move_velocity(0);
		}

		pros::delay(2);
	}
}
