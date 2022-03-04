#include "main.h"

pros::Motor lift(LIFT, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut piston(PISTON);

const int LIFT_MAX = 900;
const double LIFT_MIN = -3;

const int LIFT_MAX_VOL = 12000;
const int OP_LIFT_VOL = 12000;

const int LIFT_MAX_VEL = 100;


const int driverLiftThresh = 200;

double liftTarget = 0;
int liftPos = 0;
int liftPower;

int liftMode = 1; //0 is driver, 1 is PID
int opMode = 0; //0 is velocity control, 1 is move absolute control
/*********************************************/
bool isLiftClamped = false;
bool liftButtPress = false;

int lastSet = 0;



void clamp(bool state){
    isLiftClamped = state;
}

void liftMoveVoltage(int power){
    lift.move_voltage(power);
}

void setLiftTarget(double target){
    liftTarget = target;
}

void liftPrintInfo(){
	     //pros::lcd::print(0, "liftPos: %d\n", int(liftPos));
        // pros::lcd::print(1, "liftPos: %d\n", int(liftMode));

}

void clampPiston(bool val){
    isLiftClamped = val;
}

void setLiftMode(int mode){
    liftMode = mode;
}

void liftDelay(){
    while(fabs(liftTarget - liftPos) > 6 && !master.get_digital(DIGITAL_RIGHT)){
        liftPos = lift.get_position();
        pros::delay(20);
    }

}


void liftOp(){
    liftPos = lift.get_position();

    if(master.get_digital(DIGITAL_L1) && liftPos <= LIFT_MAX){
        opMode = 0;
        lift.move_voltage(OP_LIFT_VOL);
    }
    else if(master.get_digital(DIGITAL_L2) && liftPos >= LIFT_MIN){
        opMode = 0;
        lift.move_voltage(-OP_LIFT_VOL);
    }
    else if(opMode == 0){
        lift.move_velocity(0);
        lift.set_brake_mode(MOTOR_BRAKE_HOLD);
    }


    if(master.get_digital(DIGITAL_Y)){
        opMode = 1;
        liftTarget = LIFT_PLAT;
        lift.move_absolute(LIFT_PLAT, 100);
    }

    if(master.get_digital(DIGITAL_B)){
        opMode = 1;
        liftTarget = 0;
        lift.move_absolute(liftTarget, 100);
    }

    if(master.get_digital(DIGITAL_A)){
        opMode = 2;
    }

    if(opMode == 2){
        liftTarget = LIFT_LOW_PLAT;
        lift.move_absolute(LIFT_LOW_PLAT, 100);
        liftDelay();
        piston.set_value(false);
        isLiftClamped = false;
        pros::delay(700);
        liftTarget = LIFT_PLAT;
        lift.move_absolute(LIFT_PLAT, 100);
        opMode = 1;
    }
    //piston
    if(master.get_digital(DIGITAL_R1) && !liftButtPress){
        liftButtPress = true;
        isLiftClamped = !isLiftClamped;
    }
    else if(!master.get_digital(DIGITAL_R1)){
        liftButtPress = false;
    }

    if(isLiftClamped){
        piston.set_value(true);
    }
    else{
        piston.set_value(false);
    }

}

void tareLift(){
    lift.tare_position();
}



void liftTask(void *param){
    lift.tare_position();
	while (true){
        liftPos = lift.get_position();

        if(liftPos > driverLiftThresh){
            driver_isLiftPast = true;
        }
        else{
            driver_isLiftPast = false;
        }



        if(liftMode == 0){
            liftOp();

        }
        else if (liftMode == 1){

    		lift.move_absolute(liftTarget, LIFT_MAX_VEL);
            lift.set_brake_mode(MOTOR_BRAKE_HOLD);


            if(isLiftClamped){
                piston.set_value(true);
            }
            else{
                piston.set_value(false);
            }


        }

        liftPrintInfo();

        std::cout << liftPos << '\n';

		pros::delay(20);
	}
}
