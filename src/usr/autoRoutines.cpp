#include "main.h"

void rightNeutral(){
    clampPiston(false);

    pros::delay(1000);

    clampPiston(true);

}

void rightAlliance(){
    rightBoth();



}

void rightBoth(){
    moveForward(14);
    clampPiston(false);
    moveBackAsync(14);
    pros::delay(630);
    clampPiston(true);
    chassisWaitUntilSettled();
    turn(-50);
    moveForward(33);
    clampPiston(false);
    moveBack(28);



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
    moveForward(35);
    clampPiston(false);
    moveBack(35);

}

void leftNeutral(){
    moveForward(35);
    clampPiston(false);
    moveBack(35);
}
