#include "main.h"

void rightNeutrals(){ //backwards to first, come back, drop, forward to mid, come back, awp
    setChassisMax(127);
    setAccelStep(127);
    setLiftTarget(-2);

    //getNeutralMogo
    setGoal(true);
    moveForwardAsync(41.5);
    delayDist(41);
    clampPiston(true);
    pros::delay(130);

    moveBackAsync(25.5);
    delayDist(15);
    setLiftTarget(100);
    chassisWaitUntilSettled();


    setAccelStep(6);
    turn(215.8);
    pros::delay(20);

    setAccelStep(127);
    moveBackAsync(40.5);
    delayDist(40.5);
    setMogo(true);
    pros::delay(200);

    setAccelStep(7);
    moveForward(20);
    turn(170);
    pros::delay(20);

    moveBack(35);
    setMogo(false);
    pros::delay(150);

    moveForward(15);
    turn(48);


    moveBack(16);
    setMogo(true);
    pros::delay(150);
    setIntakeVel(500);









    // //get AWP mogo
    // setAccelStep(6);
    // turn(88);
    //
    // setAccelStep(6);
    // moveBack(11.5);
    // setMogo(true);
    // pros::delay(150);
    // setIntakeVel(500);
    //
    // moveForward(25);
    //
    //
    // clampPiston(false);
    // pros::delay(150);
    //
    // setIntakeVel(0);
    // moveBack(8.5);
    // setLiftTarget(-2);
    //
    //
    // turn(-50);
    // setGoal(true);
    // moveForward(41);
    // clampPiston(true);
    // pros::delay(150);
    // moveBack(41);
    // setGoal(false);
    //
    //
    // setMogo(false);

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
    setLiftTarget(-2);

    //getNeutralMogo
    setGoal(true);
    moveForwardAsync(41.5);
    delayDist(41);
    clampPiston(true);
    pros::delay(100);

    moveBackAsync(25.5);
    delayDist(15);
    setLiftTarget(100);
    chassisWaitUntilSettled();

    setGoal(false);



    //get AWP mogo
    setAccelStep(6);
    turn(88);

    setAccelStep(6);
    moveBack(11.5);
    setMogo(true);
    pros::delay(150);
    setIntakeVel(500);

    moveForward(25);


    clampPiston(false);
    pros::delay(150);

    setIntakeVel(0);
    moveBack(8.5);
    setLiftTarget(-2);


    turn(-50);
    setGoal(true);
    moveForward(40.5);
    clampPiston(true);
    pros::delay(150);
    moveBack(41);
    setGoal(false);


    setMogo(false);
    //
    // setChassisMax(127);
    // setAccelStep(127);
    // setLiftTarget(0);
    //
    // //getNeutralMogo
    // setGoal(true);
    // moveForwardAsync(41.5);
    // delayDist(41);
    // clampPiston(true);
    // pros::delay(130);
    //
    //
    //
    //
    // moveBackAsync(27);
    // delayDist(7);
    // setLiftTarget(200);
    // chassisWaitUntilSettled();
    //
    //
    // setAccelStep(7);
    //
    // //get AWP mogo
    // turn(90);
    //
    // setAccelStep(7);
    // moveBack(11.5);
    // setMogo(true);
    // pros::delay(400);
    // setIntakeVel(450);
    // moveForward(18);
    // setMogo(false);

}

void rightBothRush(){ //rush & goal cover to right mogo as fast as possible
    setChassisMax(127);
    setAccelStep(127);
    setLiftTarget(-2);

    //getNeutralMogo
    setGoal(true);
    moveForwardAsync(50);
    delayDist(35.5);//36
    clampPiston(true);
    pros::delay(100);

    moveBackAsync(26.2);
    delayDist(15);
    setLiftTarget(100);
    chassisWaitUntilSettled();

    //get AWP mogo
    setAccelStep(6);
    turn(90);

    setAccelStep(6);
    moveBack(14);
    setMogo(true);
    pros::delay(150);
    setIntakeVel(500);

    moveForward(25);

}

void rightNeutRush(){
    setChassisMax(127);
    setAccelStep(127);
    setLiftTarget(-2);

    //getNeutralMogo
    setGoal(true);
    moveForwardAsync(50);
    delayDist(35.5);//36
    clampPiston(true);
    pros::delay(100);

    setAccelStep(50);

    moveBackAsync(25.5);
    delayDist(15);
    setLiftTarget(100);
    chassisWaitUntilSettled();


    setAccelStep(6);
    turn(216.5);
    pros::delay(20);

    setAccelStep(9);
    moveBackAsync(40.5);
    delayDist(40.5);
    setMogo(true);
    pros::delay(200);

    setAccelStep(7);
    moveForward(20);
    turn(170);
    pros::delay(20);

    moveBack(35);
    setMogo(false);
    pros::delay(150);

    moveForward(15);
    turn(51);


    moveBack(13);
    setMogo(true);
    pros::delay(150);
    setIntakeVel(500);

}



void rightMidRush(){ // rush mid & come back

    setChassisMax(127);
    setAccelStep(127);
    setLiftTarget(-2);

    setGoal(true);


    moveForwardAsync(80);

    delayDist(64);
    clampPiston(true);
    pros::delay(100);
    moveBack(60);

}

void rightFakeMid(){ // fake right, get mid

    setChassisMax(127);
    setAccelStep(8);
    setLiftTarget(-2);
    setGoal(true);

    moveForward(15);
    turn(41.5);
    pros::delay(50);


    moveForwardAsync(50);
    delayDist(34);
    clampPiston(true);
    pros::delay(100);
    moveBack(50);



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


        setChassisMax(127);
        setAccelStep(127);

        setGoal(true);

        setLiftTarget(0);



        //grab left neutral

        moveForwardAsync(55);//45
        delayDist(39);
        clampPiston(true);
        pros::delay(100);

        moveBackAsync(36);
        delayDist(15);
        setLiftTarget(100);
        chassisWaitUntilSettled();

        setAccelStep(7);

        //turn to get alliance mogo
        turn(65);

        setAccelStep(30);

        moveBack(9.2);

        setMogo(true);
        pros::delay(150);

        moveForwardAsync(12);
        delayDist(5);
        setIntakeVel(500);
        chassisWaitUntilSettled();
        pros::delay(3000);

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
