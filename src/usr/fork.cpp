#include "main.h"

pros::Motor forkLift(18, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);



const int FORK_MAX = 490;
const double FORK_MIN = 5;

const int FORK_LOW = 470;
const int FORK_HIGH = 230;

const double FORK_KP = 35;
const double FORK_KI = 0;
const double FORK_KD = 0;

const int FORK_THRESHOLD_ERROR = 100;

const int FORK_MAX_VEL = 110;
const int OP_FORK_VEL = 80;


int forkLiftTarget = 0;
static double forkLiftDeriv = 0;
double forkLiftError = 0;
double forkLiftPos = 0;
double forkLiftGains = 0;

int forkLiftMode = 1; //0 is driver, 1 is auton


/*********************************************/





void setForkTarget(double target){
    forkLiftTarget = target;
}

void forkPrintInfo(){
	    pros::lcd::print(4, "forkLiftPos: %d\n", int(forkLiftPos));
}

void setForkMode(int mode){
    forkLiftMode = mode;
}


void forkOp(){
    int forkLiftVel = 0;
    forkLift.set_brake_mode(MOTOR_BRAKE_HOLD);


    //velocity based fork control
    // if(master.get_digital(DIGITAL_X) && forkLiftPos <= FORK_MAX){
    //     forkLiftVel = OP_FORK_VEL;
    // }
    // else if(master.get_digital(DIGITAL_B) && forkLiftPos >= FORK_MIN){
    //     forkLiftVel = -OP_FORK_VEL;
    // }
    // forkLift.move_velocity(forkLiftVel);

    //absolute fork control


    if(master.get_digital(DIGITAL_X) && forkLiftPos <= FORK_MAX){
        forkLiftTarget = FORK_LOW;
    }
    else if(master.get_digital(DIGITAL_B) && forkLiftPos >= FORK_MIN){
        forkLiftTarget = FORK_HIGH;
    }
    forkLift.move_absolute(forkLiftTarget, FORK_MAX_VEL);


}


void forkTask(void *param){
    forkLift.tare_position();
	while (true)
	{

        if(forkLiftMode == 0){
            forkOp();
        }
        else{
    		forkLift.move_absolute(forkLiftTarget, FORK_MAX_VEL);
            forkLift.set_brake_mode(MOTOR_BRAKE_HOLD);
        }

        forkLiftPos = forkLift.get_position();
        //forkPrintInfo();

		pros::delay(20);
	}
}
