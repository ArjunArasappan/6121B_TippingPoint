#include "main.h"

void rightNeutral(){
    moveForward(33.5);
    clampPiston(false);
    moveBack(32);

}

void rightAlliance(){




}

void rightBoth(){
    moveForward(14.5);
    clampPiston(false);
    moveBackAsync(14);
    pros::delay(630);
    clampPiston(true);
    chassisWaitUntilSettled();
    turn(-48);
    moveForward(34);
    clampPiston(false);
    moveBack(27);



}

void leftBoth(){
    //moveForward(3);
    clampPiston(false);

    pros::delay(500);

    clampPiston(true);

    _leftReset();
    _rightReset();
    moveBackAsync(8);
    chassisWaitUntilSettled();

    turn(-67);
    moveForward(36);
    clampPiston(false);
    moveBack(35);

}

void leftNeutral(){
    moveForward(35);
    clampPiston(false);
    moveBack(35);
}
