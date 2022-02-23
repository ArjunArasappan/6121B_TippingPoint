#include "main.h"

void rightNeutrals(){
    setAccelStep(6);

    //getNeutralMogo
    // moveBackAsync(30);
    // delayDist(29.5);
    moveBackAsync(30);
    delayDist(29.6);
    setMogo(true);
    chassisWaitUntilSettled();
    pros::delay(100);
    moveForward(23);

    //release neutral mogo & trun
    //setAccelStep(4);
    turn(178);
    setMogo(false);


    //get middle get middle neiutral
    moveForward(7);
    turn(46);
    moveForward(28);
    clampPiston(true);
    pros::delay(100);
    moveBackAsync(28);
    delayDist(1);
    setLiftTarget(200);
    chassisWaitUntilSettled();
    turn(46);

    //get AWP
    moveBack(10);
    setMogo(true);
    pros::delay(100);
    setIntakeVel(100);
    moveForward(11);
    setMogo(false);

}


void rightBoth(){

    setChassisMax(12000);
    setAccelStep(8);

    //getNeutralMogo
    moveForward(30);
    pros::delay(10);
    clampPiston(true);
    pros::delay(200);
    setLiftTarget(200);
    pros::delay(50);
    moveBack(17);

    setAccelStep(6);

    //get AWP mogo
    setChassisMax(9000);
    turn(90);

    setAccelStep(4);
    moveBack(10.5);
    setMogo(true);
    pros::delay(400);
    setIntakeVel(140);
    moveForward(18);
    setIntakeVel(0);
    setMogo(false);



}



void leftNeutrals(){

    setAccelStep(6);


    //grab left neutral
    moveForward(32.3);
    clampPiston(true);
    pros::delay(100);
    moveBackAsync(34.8);
    delayDist(1);
    setLiftTarget(200);
    chassisWaitUntilSettled();

    //turn to get alliance mogo
    turn(99);
    moveBack(6);
    setMogo(true);
    pros::delay(100);
    setIntakeVel(100);
    moveForward(5);
    setMogo(false);


}

void leftBoth(){

    setChassisMax(12000);

    //deposit ring
    moveForward(3);
    clampPiston(true);
    pros::delay(100);
    clampPiston(false);
    pros::delay(70);
    moveBack(8);

    //turn & get neutral mogo

    turn(72);
    moveForward(38);
    clampPiston(true);
    moveBack(35);


}



void soloAWP(){

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
