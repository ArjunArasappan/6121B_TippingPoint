#include "main.h"

pros::ADIDigitalOut mogoIn(MOGO_IN);
pros::ADIDigitalOut mogoOut(MOGO_OUT);


bool isMogoClamped = false; //false is out, true is active clamp
bool buttonPress = false;

int mogoMode = 1; //1 is auto, 0 is opcontrol
int clickTimer = 0;

void setMogoMode(int val){
    mogoMode = val;
}

void setMogo(bool state){
    isMogoClamped = state;
}

void mogoOp(){
    if(master.get_digital(DIGITAL_UP) && !buttonPress){
        buttonPress = true;
        isMogoClamped = !isMogoClamped;
    }
    else if(!master.get_digital(DIGITAL_UP)){
        buttonPress = false;
    }
}



void mogoTask(void *param){
	while (true){

        if(mogoMode == 0){
            mogoOp();
        }

        if(isMogoClamped){
            mogoIn.set_value(true);
            mogoOut.set_value(false);
            pros::lcd::print(0, "clamp: %d\n", 0);
        }
        else{
            mogoIn.set_value(false);
            mogoOut.set_value(true);
            pros::lcd::print(0, "release: %d\n", 0);
        }

		pros::delay(20);
	}
}
