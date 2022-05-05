#include "main.h"

void rightNeutrals(){ //backwards to first, come back, drop, forward to mid, come back, awp
    setChassisMax(127);
    setAccelStep(127);
    setLiftTarget(0);

    //getNeutralMogo
    setGoal(true);
    moveForwardAsync(41.5);
    delayDist(41);
    clampPiston(true);
    pros::delay(130);




    moveBackAsync(27);
    delayDist(7);
    setLiftTarget(100);
    chassisWaitUntilSettled();
    setGoal(false);


    setAccelStep(6);

    //get AWP mogo
    turn(90);

    setAccelStep(7);
    moveBack(11.5);
    setMogo(true);
    pros::delay(150);
    setIntakeVel(500);
    moveForward(25);
    clampPiston(false);
    moveBack(7);

    setGoal(true);
    turn(-45);
    moveForward(40.5);
    delayDist(40.5);
    clampPiston();
    pros::delay(150);
    moveBack(40.5)

    delay


    setMogo(false);

    // setChassisMax(127);
    // setAccelStep(127);
    // setLiftTarget(0);
    //
    // //getNeutralMogo
    // moveBack(45.4); // used to be moveBack(45.6);
    // pros::delay(100);
    // setMogo(true);
    // pros::delay(150);
    // moveForward(36);
    //
    // //release neutral mogo & trun
    // //setAccelStep(4);
    // turn(180);
    // setMogo(false);
    // pros::delay(150);
    //
    //
    // //get middle get middle neiutral
    // moveForward(9.5);
    // turn(50);//50
    // setChassisMax(110);
    // setGoal(true);
    // moveForward(40.5);
    // clampPiston(true);
    // pros::delay(150);
    // setChassisMax(127);
    // moveBackAsync(42);
    // delayDist(2);
    // setLiftTarget(200);
    // chassisWaitUntilSettled();
    // turn(42.5);
    //
    // //get AWP
    // moveBack(11.5);
    // setMogo(true);
    // pros::delay(150);
    // setIntake(true);
    // moveForward(17);
    // setMogo(false);

}

void rightBoth(){ // rush forward & goal cover to first, come back & awp
    setChassisMax(127);
    setAccelStep(127);
    setLiftTarget(0);

    //getNeutralMogo
    setGoal(true);
    moveForwardAsync(41.5);
    delayDist(41);
    clampPiston(true);
    pros::delay(130);




    moveBackAsync(27);
    delayDist(7);
    setLiftTarget(200);
    chassisWaitUntilSettled();


    setAccelStep(7);

    //get AWP mogo
    turn(90);

    setAccelStep(7);
    moveBack(11.5);
    setMogo(true);
    pros::delay(400);
    setIntakeVel(450);
    moveForward(18);
    setMogo(false);

}

void rightRush(){ //rush & goal cover to right mogo as fast as possible
    rightNeutrals();


}



void rightMidRush(){ // rush mid & come back

    setChassisMax(127);
    setAccelStep(127);
    setLiftTarget(-2);

    moveForward(69.5);
    clampPiston(true);
    pros::delay(100);
    moveBack(60);

}

void rightFakeMid(){ // fake right, get mid

    setChassisMax(127);
    setAccelStep(8);
    setLiftTarget(-2);

    moveForward(15);
    turn(45);
    moveForwardAsync(46.5);
    delayDist(46);
    clampPiston(true);
    pros::delay(100);
    moveBack(60);



}

void progSkills(){
    setMogo(true);
    pros::delay(100);
    setLiftTarget(200);
    turn(90);
    setIntakeVel(150);
    pros::delay(2000);
    setIntakeVel(0);
    setLiftTarget(0);
    pros::delay(500);

    moveBack(80);
}


void leftNeutrals(){ // rush forward & goal cover to left yellow, come back & do awp


    setChassisMax(127);
    setAccelStep(127);

    setGoal(true);

    setLiftTarget(0);



    //grab left neutral

    moveForwardAsync(45.5);//45
    delayDist(44.5);
    clampPiston(true);
    pros::delay(100);

    moveBackAsync(36);
    delayDist(15);
    setLiftTarget(100);
    chassisWaitUntilSettled();

    setAccelStep(7);

    //turn to get alliance mogo
    turn(61);

    setAccelStep(30);

    moveBack(9.2);

    setMogo(true);
    pros::delay(150);

    moveForwardAsync(12);
    delayDist(5);
    setIntakeVel(500);
    chassisWaitUntilSettled();
    pros::delay(3000);
    setMogo(false);


}

void leftBoth(){
    leftNeutrals();

    // setAccelStep(7);
    //
    //
    // //grab left neutral
    // moveForward(46);
    // clampPiston(true);
    // pros::delay(100);
    // moveBackAsync(48);
    // delayDist(1);
    // setLiftTarget(200);
    // chassisWaitUntilSettled();
    //
    // //turn to get alliance mogo
    // turn(90);
    // moveBack(9);
    // setMogo(true);
    // pros::delay(100);
    // setIntake(true);
    // moveForward(7);
    // pros::delay(3000);
    // setMogo(false);

}

void leftRush(){ // rush left & come back
    leftNeutrals();
}



void soloAWP(){// solo awp

    setChassisMax(12000);

    //deposit ring
    moveForward(3);
    clampPiston(true);
    pros::delay(100);
    clampPiston(false);
    pros::delay(70);

    // move back and point towards mogo
    moveBack(10);
    turn(-90);
    moveBack(15);
    turn(-88);


    //deposit rings on mogo
    setChassisMax(10000);
    moveBack(74);
    setMogo(true);
    setLiftTarget(200);
    pros::delay(600);
    setIntakeVel(200);
    moveForward(18);
    setIntakeVel(0);

    // moveForward(14.5);
    // clampPiston(true);
    // moveBackAsync(14);
    // pros::delay(500);
    // clampPiston(false);
    // chassisWaitUntilSettled();
    // turn(48);
    // moveForward(16);
    // turn(90);
    // moveForward(34);



}
