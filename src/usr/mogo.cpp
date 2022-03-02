#include "main.h"

pros::ADIDigitalOut mogo(MOGO_CLAMP);



bool isMogoClamped = false; //false is out, true is active clamp
bool mogoButtPress = false;

int mogoMode = 1; //1 is auto, 0 is opcontrol
int clickTimer = 0;

void setMogoMode(int val){
    mogoMode = val;
}

void setMogo(bool state){
    isMogoClamped = state;
}

void mogoOp(){
    if(master.get_digital(DIGITAL_X) && !mogoButtPress){
        mogoButtPress = true;
        isMogoClamped = !isMogoClamped;
    }
    else if(!master.get_digital(DIGITAL_X)){
        mogoButtPress = false;
    }
}



void mogoTask(void *param){
	while (true){

        if(mogoMode == 0){
            mogoOp();
        }

        if(isMogoClamped){
            mogo.set_value(true);
            //pros::lcd::print(0, "clamp: %d\n", 0);
        }
        else{
            mogo.set_value(false);
            //pros::lcd::print(0, "release: %d\n", 0);
        }

		pros::delay(20);
	}
}
