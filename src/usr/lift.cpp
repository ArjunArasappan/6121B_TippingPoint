#include "main.h"

pros::Motor lift(LIFT, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut piston(PISTON);







const int LIFT_MAX = 950;
const double LIFT_MIN = -1;

const double LIFT_KP = 35;
const double LIFT_KI = 0;
const double LIFT_KD = 0;

const int LIFT_MAX_VOL = 12000;
const int OP_LIFT_VOL = 12000;

const int LIFT_INTEGRAL_BOUNDS[] = {30, 5};
const int LIFT_INTEGRAL_CAP = 0;

const int MAX_LIFT_POWER = 100;
const int LIFT_MAX_VEL = 100;

double liftTarget = 0;
static double liftDeriv = 0;
double liftError = 0;
double liftLastError = 0;
double liftPos = 0;
double liftGains = 0;
double liftIntegral = 0;

int liftIter = 0;
int liftPower = 0;

int liftMode = 1; //0 is driver, 1 is PID
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

void liftMoveVoltage(int power){
    lift.move_voltage(power);
}

void setLiftTarget(double target){
    liftTarget = target;
}

void liftPrintInfo(){
	    pros::lcd::print(3, "liftPos: %d\n", int(liftPos));
        pros::lcd::print(4, "deltaTime: %d\n", int(deltaTime));
        pros::lcd::print(5, "deltaTime: %b\n", isClamped);

}

void clampPiston(bool val){
    isClamped = val;
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

    lift.set_brake_mode(MOTOR_BRAKE_HOLD);


    //lift
    // if(master.get_digital(DIGITAL_L1) && liftPos <= LIFT_MAX){
    //     liftVel = OP_LIFT_VEL;
    // }
    // else if(master.get_digital(DIGITAL_L2) && liftPos >= LIFT_MIN){
    //     liftVel = -OP_LIFT_VEL;
    // }
    // lift.move_velocity(liftVel);

    if(master.get_digital(DIGITAL_L1) && liftPos <= LIFT_MAX){
        liftPower = MAX_LIFT_POWER;
    }
    else if(master.get_digital(DIGITAL_L2) && liftPos >= LIFT_MIN){
        liftPower = -MAX_LIFT_POWER;
    }
    else{
        liftPower = 0;
    }
    lift.move_velocity(liftPower);


    //piston
    if(master.get_digital(DIGITAL_R1)){
        piston.set_value(true);
    }
    else if(!master.get_digital(DIGITAL_R1)){
        piston.set_value(false);
    }

}




void liftTask(void *param){
    lift.tare_position();

	while (true)
	{
        int liftIter = 0;
        if(liftMode == 0){
            liftOp();
            liftIter = 0;
        }
        else if (liftMode == 1){
            liftIter++;
            liftError = liftTarget - liftPos;
            if(liftIter == 0){
                liftLastError = liftError;
            }
            liftDeriv = liftError - liftLastError;

            //calcs integral in bounds
            if(fabs(liftError) < LIFT_INTEGRAL_BOUNDS[0] && fabs(liftError) > LIFT_INTEGRAL_BOUNDS[1]){
                liftIntegral += liftError;
            }
            else{
                liftIntegral = 0;
            }

            //caps integral
            // if (liftIntegral > LIFT_INTEGRAL_CAP) {
            //     liftIntegral = LIFT_INTEGRAL_CAP;
            // }

            liftGains =  LIFT_KP * liftError + LIFT_KD * liftDeriv + LIFT_KI * liftIntegral;

            liftMoveVoltage(liftGains);

    		lift.move_absolute(liftTarget, LIFT_MAX_VEL);
            lift.set_brake_mode(MOTOR_BRAKE_HOLD);



            liftLastError = liftError;
            liftIter++;

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
