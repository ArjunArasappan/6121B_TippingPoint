#include "main.h"

pros::Motor lift(LIFT, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut piston(PISTON);


const int LIFT_MAX = 950;
const double LIFT_MIN = 5;

const double LIFT_KP = 35;
const double LIFT_KI = 0;
const double LIFT_KD = 0;

const int LIFT_THRESHOLD_ERROR = 100;

const int LIFT_MAX_VEL = 200;
const int OP_LIFT_VEL = 80;


int liftTarget = 0;
static double liftDeriv = 0;
double liftError = 0;
double liftPos = 0;
double liftGains = 0;

int liftMode = 1; //0 is driver, 1 is auton

/*********************************************/
int lastTime = 0;
int deltaTime = 0;
int pistonThresh = 50;
bool isClamped = false;

bool lastState = false;
bool currentState = false;


void clamp(bool state){
    isClamped = state;
}


void setLiftTarget(double target){
    liftTarget = target;
}

void liftPrintInfo(){
	    pros::lcd::print(3, "liftPos: %d\n", int(liftPos));
        pros::lcd::print(4, "deltaTime: %d\n", int(deltaTime));
        pros::lcd::print(5, "deltaTime: %b\n", isClamped);

}

void setLiftMode(int mode){
    liftMode = mode;
}

void calcDelta(){
    if(pros::millis() - lastTime > pistonThresh){
        deltaTime = pros::millis() - lastTime;
        lastTime = pros::millis();
    }
}

void liftOp(){
    int liftVel = 0;
    lift.set_brake_mode(MOTOR_BRAKE_HOLD);


    //lift 
    if(master.get_digital(DIGITAL_R1) && liftPos <= LIFT_MAX){
        liftVel = OP_LIFT_VEL;
    }
    else if(master.get_digital(DIGITAL_R2) && liftPos >= LIFT_MIN){
        liftVel = -OP_LIFT_VEL;
    }
    lift.move_velocity(liftVel);


    //piston
    if(master.get_digital(DIGITAL_L1)){
        piston.set_value(true);
    }
    else if(master.get_digital(DIGITAL_L2)){
        piston.set_value(false);
    }

}


void liftTask(void *param){
    lift.tare_position();
	while (true)
	{

        if(liftMode == 0){
            liftOp();
        }
        else{
    		lift.move_absolute(liftTarget, LIFT_MAX_VEL);
            lift.set_brake_mode(MOTOR_BRAKE_HOLD);

            if(isClamped){
                piston.set_value(true);
            }
            else{
                piston.set_value(false);
            }
        }



        liftPos = lift.get_position();
        liftPrintInfo();

        std::cout << liftPos << '\n';

		pros::delay(20);
	}
}
