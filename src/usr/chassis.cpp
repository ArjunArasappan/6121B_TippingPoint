#include "main.h"

pros::Motor left1(LEFTFRONT, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor leftMid(LEFTMID, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor left2(LEFTREAR, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

pros::Motor right1(RIGHTFRONT, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rightMid(RIGHTMID, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor right2(RIGHTREAR, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);


pros::Rotation rightTracker (RIGHT_TRACKING_PORT);
pros::Rotation leftTracker (LEFT_TRACKING_PORT);


static int chassisMode = 1; //1 for forward/backward; 2 for turn; 3 for point turn; 4 for arcs

const double WHEELBASE_WIDTH = 13.25;
const double TRACKING_WIDTH = 7;
const double TRACKING_OFFSET = (WHEELBASE_WIDTH - TRACKING_WIDTH) / 2;

const double WHEEL_DIAM = 4;
const double TRACK_DIAM = 2.75;
const double DRIVE_RATIO = 84/60;
const double PI = 3.14159265;

int CHASSIS_MAX = 127;
int TURN_MAX = 90; //70
int POINT_MAX = 90;
int ARC_MAX = 127;


bool isChassisLocked = false;
bool lockButtPress = false;

int driveVel = 60;

bool parkButtPress = false;
bool isParking = false;
double parkAngleThresh = 17;
double parkDist = 6;
double driveDist = 36;

static int chassis_maxSpeed = CHASSIS_MAX;
static int turn_maxSpeed = TURN_MAX;
static int point_maxSpeed = POINT_MAX;
static int arc_maxSpeed = ARC_MAX;

double P = 0;
double I = 0;
double D = 0;

int depth = 0;


const double CHASSIS_KP = 0.31;//0.3
const double CHASSIS_KI = 0.24;
const double CHASSIS_KD = 0.03;

const double TRACKING_CHASSIS_KP = 0.148;//0.148 ,0.1505
const double TRACKING_CHASSIS_KI = 0.012;//0.012 ,0.001
const double TRACKING_CHASSIS_KD = 0.160;//0.160 ,0.01


const double CHASSIS_ERROR_TRESH[] = {60, 10}; //1st bound starts timer, 2nd bound is for exit condition //{60,7}
const double CHASSIS_DERIV_THRESH = 3; //derivative threshold //3
const int CHASSIS_TIMEOUT[] = {5000, 170}; //max settling time //1300, 120

const double CHASSIS_LOWER_INTEGRAL_BOUND = CHASSIS_ERROR_TRESH[1];//5
const double CHASSIS_UPPER_INTEGRAL_BOUND = 130;//60
const double CHASSIS_INTEGRAL_CAP = 0;

double chassisVolts = 8;

int chassisAccelStep = 0;

//left
double leftTarget = 0;
double leftPos = 0;

double leftError = 0;
double lastLeftError = 0;
double leftDeriv = 0;
double leftIntegral = 0;

double leftPower = 0;
double slewedLeftPower = 0;
double lastSlewedLeftPower = 0;


double leftLastDeriv = 0;

int leftSettleTimer = 0;
int leftExitTimer = 0;


//right
double rightTarget = 0;
double rightPos = 0;
double rightError = 0;

double lastRightError = 0;
double rightDeriv = 0;
double rightIntegral = 0;

double rightPower = 0;
double slewedRightPower = 0;
double lastSlewedRightPower = 0;


double rightLastDeriv = 0;

int rightSettleTimer = 0;
int rightExitTimer = 0;


/**************************************************/
//turn

double turnTarget = 0;
double turnPos = 0;

double turnError = 0;
double lastTurnError = 0;
double turnDeriv = 0;

double turnLastDeriv = 0;
int turnElapsed = 0;

double turnPower = 0;

double turnIntegral = 0;

const double TURN_KP = 0.9;
const double TURN_KI = 0.0;
const double TURN_KD = 3.0;

const double TRACKING_TURN_KP = 0.45;
const double TRACKING_TURN_KI = 0.01;
const double TRACKING_TURN_KD = 1.5;

const double TURN_ERROR_MIN = 0;



const double TURN_ERROR_TRESH[] = {10, 5}; //{15, 7}
const double TURN_DERIV_THRESH = 4; //2
const double TURN_TIMEOUT = 1000;

const double TURN_LOWER_INTEGRAL_BOUND = TURN_ERROR_TRESH[4];
const double TURN_UPPER_INTEGRAL_BOUND = 120;
const double TURN_INTEGRAL_CAP = 0;

int turnAccelStep = 0;

//delay distance

bool isRightPast = false;
bool isLeftPast = false;

double degDist = 0;
double inchFist = 0;

/**************************************************/
//point turns
bool isPointTurnRight = true;

const double TRACKING_POINT_KP = 0.35;//0.3
const double TRACKING_POINT_KI = 0.05;
const double TRACKING_POINT_KD = 0.45;


const double POINT_ERROR_TRESH[] = {20, 4}; //1st bound starts timer, 2nd bound is for exit condition //{60,7}
const int POINT_TIMEOUT[] = {9000, 150}; //max settling time //1300, 120

const double POINT_LOWER_INT_BOUND = POINT_ERROR_TRESH[1];
const double POINT_UPPER_INT_BOUND = 30;


/**************************************************/
//arc
double arcRatio = 0;
bool isArcRight = true;

const double ARC_KP[] = {0, 0};
const double ARC_KI[] = {0, 0};
const double ARC_KD[] = {0, 0};


/**************************************************/
//slant

bool needSlant = true;

double slantDiff = 0;
double slantGains = 0;
double lastSlantDiff = 0;
double slantDeriv = 0;

const double SLANT_KP = 0.00; //0.05
const double SLANT_KI = 0.00; //0.003
const double SLANT_KD = 0.00;

const double SLANT_ACTIV_THRESH = 3;//0.6
const double SLANT_SETTLE_OFFSET = 999;

const double SLANT_LOWER_INTEGRAL_BOUND = SLANT_ACTIV_THRESH;//5
const double SLANT_UPPER_INTEGRAL_BOUND = 40;//60


double slantIntegral = 0;


const double SLANT_TURN_KP = 0.0;
const double SLANT_TURN_KD = 0;




double slantState = 0;

const double ARC_SLANT_KP = 0;
const double ARC_SLANT_KD = 0;

//*************************************************/
//setters
void setChassisMax(int power){
    CHASSIS_MAX = power;
}

void setTurnMax(int power){
    TURN_MAX = power;
}

void setChassisMode(int mode){
    chassisMode = mode;
}
/**************************************************/
//basic functions

int sgn(int value){
    return abs(value) / value;
}

double toDouble(float val){
    int val2 = (val * 100000.0);
    return (double)(val2 / 100000.0);
}

double sgn(double value){
    return abs(value) / value;
}

double inchesToTicks(double inches){
	double revolutions = inches / (WHEEL_DIAM * PI);
	return revolutions * 360 / DRIVE_RATIO;
}

double degreesToTicks(double degrees){
	double distance_inches = ( PI * WHEELBASE_WIDTH * degrees) / 360.0;
	double revolutions = (distance_inches / (WHEEL_DIAM * PI));
	return revolutions * 360 * 60 / 84;
}

double tracking_inchesToTicks(double inches){
    double revolutions = inches / (TRACK_DIAM * PI);
	return revolutions * 360;
}

double tracking_degreesToTicks(double degrees){
    double distance_inches = (PI * TRACKING_WIDTH * degrees) / 360.0;
    double revolutions = (distance_inches / (TRACK_DIAM * PI));
    return revolutions * 360;
}

/**************************************************/
//basic control
void setChassisVel(double vel){
    left1.move_velocity(vel);
    leftMid.move_velocity(vel);
    left2.move_velocity(vel);

    right1.move_velocity(vel);
    rightMid.move_velocity(vel);
    right2.move_velocity(vel);
}

void left(int power){
    left1.move(power);
    leftMid.move(power);
    left2.move(power);
}

void right(int power){
    right1.move(power);
    rightMid.move(power);
    right2.move(power);
}

void lockLeft(){
    left1.move_velocity(0);
    leftMid.move_velocity(0);
    left2.move_velocity(0);

    left1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftMid.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    left2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void lockRight(){
    right1.move_velocity(0);
    rightMid.move_velocity(0);
    right2.move_velocity(0);

    right1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightMid.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    right2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void coastLeft(){
    left1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftMid.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    left2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void coastRight(){
    right1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightMid.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    right2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}


void reset(){
    depth = 0;
    coastRight();
    coastLeft();
    imu.tare_rotation();
    imu.tare_pitch();

}

double getRightPos(){
    //return right1.get_position();
    return rightTracker.get_position() / 100.0;
}

double getLeftPos(){
    //return left1.get_position();
    return leftTracker.get_position() / 100.0;
}

float getHeading(){
    return imu.get_rotation();;
}
float getPitch(){
    return imu.get_pitch();
}

void _leftReset()
{
    left1.tare_position();
    leftMid.tare_position();
    left2.tare_position();

    leftTracker.reset_position();

    coastLeft();

    leftPos = 0;
    leftError = 0;

    lastLeftError = 0;
    leftDeriv = 0;
    leftIntegral = 0;

    leftPower = 0;
    slewedLeftPower = 0;
    //lastSlewedLeftPower = 0;

    leftLastDeriv = 0;

    leftSettleTimer = 0;
    leftExitTimer = 0;


    left(0);
}

void _rightReset()
{
    right1.tare_position();
    rightMid.tare_position();
    right2.tare_position();

    rightTracker.reset_position();

    coastRight();

    rightPos = 0;
    rightError = 0;

    lastRightError = 0;
    rightDeriv = 0;
    rightIntegral = 0;

    rightPower = 0;
    slewedRightPower = 0;
    //lastSlewedRightPower = 0;

    rightLastDeriv = 0;

    rightSettleTimer = 0;
    rightExitTimer = 0;

    right(0);
}

/**************************************************/
//slew control
int accel_step = 7; //default acceleration
int decel_step = 256; // no decel slew
int accel;
int decel;

int step;
int direc;

void setAccelStep(int st){
    accel_step = st;
}


void leftSlew(int pwr){
    direc = sgn(pwr); //1
    accel = accel_step; //8
    decel = decel_step; //-256

    // if(chassisMode == 1 && chassisAccelStep != 0)
    //     accel = chassisAccelStep;
    //
    // if(chassisMode == 2 && chassisAccelStep != 0)
    //     accel = turnAccelStep;
    if(depth == 0){
        accel = chassisVolts;
    }
    else{
        accel = accel_step;
    }


    if(abs(pwr) > abs(lastSlewedLeftPower)){ // accel
        if(abs(pwr) > abs(lastSlewedLeftPower) + accel){
            pwr = lastSlewedLeftPower + accel * direc;
        }
    }

    else  // deccel
        if(abs(pwr) < abs(lastSlewedLeftPower) - decel)
            pwr = lastSlewedLeftPower + decel * direc;

    lastSlewedLeftPower = pwr;
    slewedLeftPower = pwr;

    // if(chassisMode == 4)
    //     if(!isArcRight)
    //         slewedLeftPower = slewedLeftPower * arcRatio;



    left(slewedLeftPower);
}


void rightSlew(int pwr){
    direc = sgn(pwr);
    accel = accel_step;
    decel = decel_step;

    // if(chassisMode == 1 && chassisAccelStep != 0)
    //     accel = chassisAccelStep;
    //
    // if(chassisMode == 2 && chassisAccelStep != 0)
    //     accel = turnAccelStep;

    if(depth == 0){
        accel = chassisVolts;
    }
    else{
        accel = accel_step;
    }

    if(abs(pwr) > abs(lastSlewedRightPower)) // accel
        if(abs(pwr) > abs(lastSlewedRightPower) + accel)
            pwr = lastSlewedRightPower + accel * direc;

    else  // deccel
        if(abs(pwr) < abs(lastSlewedRightPower) - decel)
            pwr = lastSlewedRightPower + decel * direc;

    lastSlewedRightPower = pwr;
    slewedRightPower = pwr;

    // if(chassisMode == 4)
    //     if(!isArcRight)
    //         slewedRightPower = slewedRightPower * arcRatio;



    right(slewedRightPower);
}

int returnRightSlew(int pwr){
    direc = sgn(pwr);
    accel = accel_step;
    decel = decel_step;

    if(abs(pwr) > abs(lastSlewedRightPower)) // accel
        if(abs(pwr) > abs(lastSlewedRightPower) + accel)
            pwr = lastSlewedRightPower + accel * direc;

    else  // deccel
        if(abs(pwr) < abs(lastSlewedRightPower) - decel)
            pwr = lastSlewedRightPower + decel * direc;

    lastSlewedRightPower = pwr;
    slewedRightPower = pwr;
    return slewedRightPower;
}

int returnLeftSlew(int pwr){
    direc = sgn(pwr); //1
    accel = accel_step; //8
    decel = decel_step; //-256


    if(abs(pwr) > abs(lastSlewedLeftPower)){ // accel
        if(abs(pwr) > abs(lastSlewedLeftPower) + accel){
            pwr = lastSlewedLeftPower + accel * direc;
        }
    }

    else  // deccel
        if(abs(pwr) < abs(lastSlewedLeftPower) - decel)
            pwr = lastSlewedLeftPower + decel * direc;

    lastSlewedLeftPower = pwr;
    slewedLeftPower = pwr;
    return slewedLeftPower;
}

/**************************************************/
//slop correction
void slop(int sp){
    chassisMode = 2;
    if(sp < 0){
        right(-30);
        pros::delay(100);
    }
    chassisMode = 1;
}

/**************************************************/
//settling conditions



bool isRightSettled(){

    if(fabs(rightError) < CHASSIS_ERROR_TRESH[0]){
        if(fabs(rightError) <= CHASSIS_ERROR_TRESH[1]){
            rightSettleTimer += 20;
        }
        else{
            rightSettleTimer = 0;
        }

        rightExitTimer += 20;

        if(rightSettleTimer > CHASSIS_TIMEOUT[1]){
            if(chassisMode == 1){
                if(fabs(slantDiff) <= SLANT_ACTIV_THRESH + SLANT_SETTLE_OFFSET){
                    return true;
                }
            }
            else{
                return true;
            }
        }
        else if(rightExitTimer > CHASSIS_TIMEOUT[0])
            return true;

        return false;
    }
    else
        rightExitTimer = 0;

    return false;
}

bool isLeftSettled(){

    if(fabs(leftError) < CHASSIS_ERROR_TRESH[0]){
        if(fabs(leftError) <= CHASSIS_ERROR_TRESH[1]){
            leftSettleTimer += 20;
        }
        else{
            leftSettleTimer = 0;
        }

        leftExitTimer += 20;

        if(leftSettleTimer > CHASSIS_TIMEOUT[1]){
            if(chassisMode == 1){
                if(fabs(slantDiff) <= SLANT_ACTIV_THRESH + SLANT_SETTLE_OFFSET){
                    return true;
                }
            }
            else{
                return true;
            }
        }


        else if(leftExitTimer > CHASSIS_TIMEOUT[0])
            return true;

        return false;
    }
    else
        leftExitTimer = 0;

    return false;
}

bool isTurnSettled(){

    if(fabs(turnError) < TURN_ERROR_TRESH[0]){
        if( fabs(turnError) < TURN_ERROR_TRESH[1] &&
            turnDeriv < TURN_DERIV_THRESH &&
            turnLastDeriv < TURN_DERIV_THRESH)
            return true;
        else if(turnElapsed > TURN_TIMEOUT)
            return true;

        turnElapsed += 20;
        return false;
    }
    return false;
}

bool isRightPointSettled(){

    if(fabs(rightError) < POINT_ERROR_TRESH[0]){
        if(fabs(rightError) <= POINT_ERROR_TRESH[1]){
            rightSettleTimer += 20;
        }
        else{
            rightSettleTimer = 0;
        }

        rightExitTimer += 20;

        if(rightSettleTimer > POINT_TIMEOUT[1]){
            return true;
        }
        else if(rightExitTimer > POINT_TIMEOUT[0])
            return true;

        return false;
    }
    else
        rightExitTimer = 0;

    return false;
}

bool isLeftPointSettled(){

    if(fabs(leftError) < POINT_ERROR_TRESH[0]){
        if(fabs(leftError) <= POINT_ERROR_TRESH[1]){
            leftSettleTimer += 20;
        }
        else{
            leftSettleTimer = 0;
        }

        leftExitTimer += 20;

        if(leftSettleTimer > POINT_TIMEOUT[1]){
            return true;
        }
        else if(leftExitTimer > CHASSIS_TIMEOUT[0])
            return true;

        return false;
    }
    else
        leftExitTimer = 0;

    return false;
}

void leftWaitUntilSettled(){
    while(!isLeftSettled()) { pros::delay(20);}
}

void rightWaitUntilSettled(){
    while(!isRightSettled()) { pros::delay(20);}
}

void leftPointWaitUntilSettled(){
    while(!isLeftPointSettled()) { pros::delay(20);}
}

void rightPointWaitUntilSettled(){
    while(!isRightPointSettled()) { pros::delay(20);}
}

void turnWaitUntilSettled(){
    while(!isTurnSettled()) { pros::delay(20);}
}

void delayDist(double dist){
    isRightPast = false;
    isLeftPast = false;
    degDist = inchesToTicks(dist);
    while(!isRightPast || !isLeftPast){
        if(abs(rightPos) > degDist){
            isRightPast = true;
        }
        if(abs(leftPos) > degDist){
            isLeftPast = true;
        }

        pros::delay(20);
    }
}


void chassisWaitUntilSettled(){
    while(true) {
        pros::delay(20);
        switch (chassisMode) {
            case 1:
                leftWaitUntilSettled();
                rightWaitUntilSettled();
                break;

            case 2:
                turnWaitUntilSettled();
                break;

            case 3:
                if(isPointTurnRight){
                    leftPointWaitUntilSettled();
                }
                else{
                    rightPointWaitUntilSettled();
                }
                break;

            case 4:
                if(isArcRight)
                    leftWaitUntilSettled();
                else
                    rightWaitUntilSettled();
            break;
    }
    break;
}

}

/**************************************************/
//autonomous functions

void parkPlat(){
    reset();
    _leftReset();
    _rightReset();

    setChassisVel(driveVel);
    while(fabs(getPitch()) < parkAngleThresh &&
          !master.get_digital(DIGITAL_RIGHT)){
        pros::delay(20);
    }


    leftTracker.reset_position();
    rightTracker.reset_position();

    while(getLeftPos() < tracking_inchesToTicks(parkDist) &&
          getRightPos() < tracking_inchesToTicks(parkDist) &&
          !master.get_digital(DIGITAL_RIGHT)){
        pros::delay(20);
    }

    setChassisVel(0);

    isChassisLocked = true;
    isParking = false;
}

void leftMoveAsync(double sp){
	_leftReset();
	leftTarget = tracking_inchesToTicks(sp);
}

void leftMove(double sp){
	leftMoveAsync(sp);
	leftWaitUntilSettled();
}

void rightMoveAsync(double sp){
	_rightReset();
	rightTarget = tracking_inchesToTicks(sp);
}

void rightMove(double sp){
	rightMoveAsync(sp);
	rightWaitUntilSettled();
}

void moveForwardAsync(double sp){
    reset();
    chassisMode = 1;
    leftMoveAsync(sp);
    rightMoveAsync(sp);
}

void moveForward(double sp){
    moveForwardAsync(sp);
    chassisWaitUntilSettled();
}

void moveBackAsync(double sp){
    moveForwardAsync(-sp);
}

void moveBack(double sp){
    chassisMode = 1;
    _leftReset();
    _rightReset();
    moveForward(-sp);
}

void turnAsync(double degrees){
    reset();
    _leftReset();
    _rightReset();
    chassisMode = 2;
	turnTarget = tracking_degreesToTicks(degrees);
}

void turn(double degrees){
    turnAsync(degrees);
    chassisWaitUntilSettled();
}

void pointTurnAsync(bool isRight, double angle){
    reset();
    _leftReset();
    _rightReset();
    chassisMode = 3;
    isPointTurnRight = isRight;

    //double outerDist = (((2 * PI * WHEELBASE_WIDTH)) * angle) / 360.0;
    double outerDist = ((2 * PI * (TRACKING_WIDTH + TRACKING_OFFSET)) * angle) / 360.0;

    if(isRight){
        lockRight();
        leftMoveAsync(outerDist);
    }
    else{
        lockLeft();
        rightMoveAsync(outerDist);
    }
}


void pointTurn(bool isRight, double angle){

    chassisMode = 3;
    pointTurnAsync(isRight, angle);
    if(isRight)
        leftWaitUntilSettled();
    else
        rightWaitUntilSettled();

}

void arcTurnAsync(double rad, double angle){
    reset();
    chassisMode = 4;

    double radius = abs(rad);

    if(rad > 0) isArcRight = true;
    else isArcRight = false;

    //arcRatio = radius / (WHEELBASE_WIDTH + radius);

    double innerDist = (2 * PI * radius * angle) / 360.0;
    double outerDist = (((2 * PI * (radius + WHEELBASE_WIDTH)) * angle) / 360);
    //double outerDist = (((2 * PI * (radius + TRACKING_WIDTH)) * angle) / 360);


    arcRatio = innerDist / outerDist;

    if(isArcRight){
        leftMoveAsync(outerDist);
        rightMoveAsync(innerDist);
    }
    else{
        leftMoveAsync(innerDist);
        rightMoveAsync(outerDist);
    }
}

void arcTurn(double rad, double angle){
    arcTurnAsync(rad,angle);
    chassisWaitUntilSettled();
}


/**************************************************/
//misc functions
void setCurrent(int mA){
    left1.set_current_limit(mA);
    left2.set_current_limit(mA);
    right1.set_current_limit(mA);
    right2.set_current_limit(mA);
}

void setBrakeMode(int mode){
    pros::motor_brake_mode_e_t brakeMode = MOTOR_BRAKE_COAST;

    switch(mode){
        case 0:
        brakeMode = MOTOR_BRAKE_COAST;
        break;
        case 1:
        brakeMode = MOTOR_BRAKE_BRAKE;
        break;
        case 2:
        brakeMode = MOTOR_BRAKE_HOLD;
        break;
    }

    left1.set_brake_mode(brakeMode);
    left2.set_brake_mode(brakeMode);
    right1.set_brake_mode(brakeMode);
    right2.set_brake_mode(brakeMode);
}

void chassisArcade(){

    int power = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_RIGHT_X);
    int leftPower = power + turn;
    int rightPower = power - turn;
    left(leftPower);
    right(rightPower);
}

int toInt(bool b){
    if(b) return 1;
    return 0;
}



void printStats(){
    if(chassisMode == 1){
        std::cout << "[" << chassisMode << ", " <<leftTarget << ", " << rightTarget << ", " << leftPos << ", " << rightPos << ", " << leftPower << ", " << rightPower  << "]" << '\n';

    }


    pros::lcd::print(0, "leftError: %d, rightError: %d\n", (int)leftError, (int)rightError);
    pros::lcd::print(1, "lSet: %d, rSet: %d, tSet: %d\n", toInt(isRightSettled()), toInt(isLeftSettled()), toInt(isTurnSettled()));
    pros::lcd::print(2, "slantDiff: %d, turnError: %d\n",  (int)slantDiff, (int)turnError);
    pros::lcd::print(3, "leftPos: %d, rightPos: %d\n", (int)getLeftPos(), (int)getRightPos());
    pros::lcd::print(4, "leftInt: %d, rightInt: %d\n", leftIntegral, rightIntegral);
    pros::lcd::print(5, "depth: %d, slantInt: %d\n", depth, (int)slantDiff);
    pros::lcd::print(6, "heading: %f, pitch: %f\n", getHeading(), getPitch());
    // pros::lcd::print(6, "{head: %d, pitch: %d, yaw: %d\n", (int)imu.get_heading(), (int)imu.get_pitch(), (int)imu.get_yaw());
    //
    // pros::lcd::print(7, "rot: %f\n", (float)imu.get_rotation());




    //pros::lcd::print(6, "turnError: %d\n", (int)turnError);

}


/**************************************************/


//task control
void chassisTask(void* parameter){

    _leftReset();
	_rightReset();
    reset();
    rightTracker.reset();
    leftTracker.reset();
	while (true){
        //opcontrol
        // if(!pros::competition::is_autonomous()){
        //     chassisArcade();
        // }
        if(chassisMode == 0){

            if(master.get_digital(DIGITAL_LEFT) && !lockButtPress){
                lockButtPress = true;
                isChassisLocked = !isChassisLocked;
            }
            else if(!master.get_digital(DIGITAL_LEFT)){
                lockButtPress = false;
            }

            if(master.get_digital(DIGITAL_UP) && !parkButtPress){
                parkButtPress = true;
                isParking = !isParking;
            }
            else if(!master.get_digital(DIGITAL_LEFT)){
                parkButtPress = false;
            }

            if(isParking){
                parkPlat();
            }
            else if(isChassisLocked){
                lockLeft();
                lockRight();
            }
            else{
                coastLeft();
                coastRight();
                chassisArcade();
            }



            printStats();
            //printStats();
        }

        //autonomous control
        else{

            //forward/backward CHASSIS
            if(chassisMode == 1){

                // P = CHASSIS_KP;
                // I = CHASSIS_KI;
                // I = CHASSIS_KD;

                P = TRACKING_CHASSIS_KP;
                I = TRACKING_CHASSIS_KI;
                D = TRACKING_CHASSIS_KD;


                /*
                LEFT CALCULATIONS
                */

                leftPos = getLeftPos();
                leftError = leftTarget - leftPos;
                leftDeriv = leftError - lastLeftError;
                //leftDeriv = sgn(leftError) * (fabs(leftError) - fabs(lastLeftError));
                lastLeftError = leftError;




                //checks if error is within integrating bounds
                if (fabs(leftError) < CHASSIS_UPPER_INTEGRAL_BOUND && fabs(leftError) > CHASSIS_LOWER_INTEGRAL_BOUND)
                    leftIntegral += leftError;
                else
                    leftIntegral = 0;

                // //caps integral
                // if (leftIntegral > CHASSIS_INTEGRAL_CAP)
                //     leftIntegral = CHASSIS_INTEGRAL_CAP;
                // else if (leftIntegral < -CHASSIS_INTEGRAL_CAP)
                //     leftIntegral = -CHASSIS_INTEGRAL_CAP;

                //calcs power
                leftPower = leftError * P + leftIntegral * I + leftDeriv * D;

                //limits to bounds
                if (leftPower > 127)
                    leftPower = 127;
                else if (leftPower < -127)
                    leftPower = -127;

                /*
                RIGHT CALCULATIONS
                */

                rightPos = getRightPos();
                rightError = rightTarget - rightPos;
                rightDeriv = rightError - lastRightError;
                lastRightError = rightError;


                //checks if error is within integrating bounds
                if (fabs(rightError) < CHASSIS_UPPER_INTEGRAL_BOUND && fabs(rightError) > CHASSIS_LOWER_INTEGRAL_BOUND)
                    rightIntegral += rightError;
                else
                    rightIntegral = 0;

                // //caps integral
                // if (rightIntegral > CHASSIS_INTEGRAL_CAP)
                //     rightIntegral = CHASSIS_INTEGRAL_CAP;
                // else if (rightIntegral < -CHASSIS_INTEGRAL_CAP)
                //     rightIntegral = -CHASSIS_INTEGRAL_CAP;

                //calcs power
                rightPower = rightError * P + rightIntegral * I + rightDeriv * D;

                //limits to bounds
                if (rightPower > 127)
                    rightPower = 127;
                else if (rightPower < -127)
                    rightPower = -127;

                /*
                SLANT CALCULATIONS
                */

                slantDiff = getLeftPos() - getRightPos();
                slantDeriv = slantDiff - lastSlantDiff;
                lastSlantDiff = slantDiff;


                if (fabs(slantDiff) < SLANT_UPPER_INTEGRAL_BOUND && fabs(slantDiff) > SLANT_LOWER_INTEGRAL_BOUND)
                    slantIntegral += slantDiff;
                else
                    slantIntegral = 0;

                slantGains = slantDiff * SLANT_KP + slantIntegral * SLANT_KI + slantDeriv * SLANT_KD;

                if (fabs(slantDiff) >= SLANT_ACTIV_THRESH){
                    leftPower -= slantGains;
                    rightPower += slantGains;
                }


                //OUTPUT

                if (leftPower > CHASSIS_MAX)
                    leftPower = CHASSIS_MAX;
                else if (leftPower < -CHASSIS_MAX)
                    leftPower = -CHASSIS_MAX;

                if (rightPower > CHASSIS_MAX)
                    rightPower = CHASSIS_MAX;
                else if (rightPower < -CHASSIS_MAX)
                    rightPower = -CHASSIS_MAX;

                leftSlew(leftPower);
                rightSlew(rightPower);

                std::cout << leftTarget << ", " << rightTarget << ", " << leftError << ", " << rightError << ", " << leftPos << ", " << rightPos << ", " << leftPower << ", " << rightPower << ", " << slewedLeftPower << ", " << slewedRightPower << ", " << lastSlewedLeftPower << ", " << lastSlewedRightPower << '\n';

                depth++;

                printStats();



            }

            //turn
            else if(chassisMode == 2){
                P = TURN_KP;
                I = TURN_KI;
                D = TURN_KD;


                /*
                TURN CALCULATIONS
                */

                turnPos = (-getLeftPos() + getRightPos()) / 2.0;
                turnError = turnTarget - turnPos;
                turnDeriv = turnError - lastTurnError;
                lastTurnError = turnError;



                //checks if error is within integrating bounds
                if (fabs(turnError) < TURN_UPPER_INTEGRAL_BOUND || fabs(leftError) >= TURN_LOWER_INTEGRAL_BOUND)
                    turnIntegral += turnError;
                else
                    turnIntegral = 0;

                //caps integral
                // if (turnIntegral > TURN_INTEGRAL_CAP)
                //     turnIntegral = TURN_INTEGRAL_CAP;
                // else if (turnIntegral < -TURN_INTEGRAL_CAP)
                //     turnIntegral = -TURN_INTEGRAL_CAP;

                //calcs power
                turnPower = turnError * P + turnIntegral * I + turnDeriv * D;

                //limits to bounds
                if (turnPower > 127)
                    turnPower = 127;
                else if (turnPower < -127)
                    turnPower = -127;

                leftPower = -turnPower;
                rightPower = turnPower;


                /*
                SLANT CALCULATIONS
                */

                slantDiff = fabs(getLeftPos()) + fabs(getRightPos());
                slantDeriv = slantDiff - lastSlantDiff;
                lastSlantDiff = slantDiff;

                slantGains = slantDiff * SLANT_TURN_KP + slantDeriv * SLANT_TURN_KD;

                if (turnError > 0){
                    leftPower -= slantGains;
                    rightPower += slantGains;
                }
                else{
                    leftPower += slantGains;
                    rightPower -= slantGains;
                }

                //OUTPUT

                if (leftPower > TURN_MAX)
                    leftPower = TURN_MAX;
                else if (leftPower < -TURN_MAX)
                    leftPower = -TURN_MAX;

                if (rightPower > TURN_MAX)
                    rightPower = TURN_MAX;
                else if (rightPower < -TURN_MAX)
                    rightPower = -TURN_MAX;

                leftSlew(leftPower);
                rightSlew(rightPower);

                printStats();
            }

            //point turn
            else if(chassisMode == 3){
                if(isPointTurnRight){
                    P = TRACKING_POINT_KP;
                    I = TRACKING_POINT_KI;
                    D = TRACKING_POINT_KD;

                    /*
                    LEFT CALCULATIONS
                    */

                    leftPos = getLeftPos();
                    leftError = leftTarget - leftPos;
                    leftDeriv = leftError - lastLeftError;
                    lastLeftError = leftError;


                    //checks if error is within integrating bounds
                    if (fabs(leftError) < POINT_UPPER_INT_BOUND && fabs(leftError) >= POINT_LOWER_INT_BOUND)
                        leftIntegral += leftError;
                    else
                        leftIntegral = 0;

                    //caps integral
                    // if (leftIntegral > CHASSIS_INTEGRAL_CAP)
                    //     leftIntegral = CHASSIS_INTEGRAL_CAP;
                    // else if (leftIntegral < -CHASSIS_INTEGRAL_CAP)
                    //     leftIntegral = -CHASSIS_INTEGRAL_CAP;

                    //calcs power
                    leftPower = leftError * P + leftIntegral * I + leftDeriv * D;

                    //limits to bounds
                    if (leftPower > 127)
                        leftPower = 127;
                    else if (leftPower < -127)
                        leftPower = -127;

                    //OUTPUT

                    if (leftPower > POINT_MAX)
                        leftPower = POINT_MAX;
                    else if (leftPower < -POINT_MAX)
                        leftPower = -POINT_MAX;

                    leftSlew(leftPower);

                    printStats();
                }
                else{
                    P = TRACKING_POINT_KP;
                    I = TRACKING_POINT_KI;
                    D = TRACKING_POINT_KD;

                    /*
                    RIGHT CALCULATIONS
                    */

                    rightPos = getRightPos();
                    rightError = rightTarget - rightPos;
                    rightDeriv = rightError - lastRightError;
                    lastRightError = rightError;


                    //checks if error is within integrating bounds
                    if (fabs(rightError) < POINT_UPPER_INT_BOUND && fabs(rightError) >= POINT_LOWER_INT_BOUND)
                        rightIntegral += rightError;
                    else
                        rightIntegral = 0;

                    // //caps integral
                    // if (rightIntegral > CHASSIS_INTEGRAL_CAP)
                    //     rightIntegral = CHASSIS_INTEGRAL_CAP;
                    // else if (rightIntegral < -CHASSIS_INTEGRAL_CAP)
                    //     rightIntegral = -CHASSIS_INTEGRAL_CAP;

                    //calcs power
                    rightPower = rightError * P + rightIntegral * I + rightDeriv * D;

                    //limits to bounds
                    if (rightPower > 127)
                        rightPower = 127;
                    else if (rightPower < -127)
                        rightPower = -127;

                    //OUTPUT
                    if (rightPower > POINT_MAX)
                        rightPower = POINT_MAX;
                    else if (rightPower < -POINT_MAX)
                        rightPower = -POINT_MAX;

                    rightSlew(rightPower);

                    printStats();
                }
            }

            //arc turn
            else if(chassisMode == 4){
                /*
                LEFT ARC CALCULATIONS
                */

                leftPos = getLeftPos();
                leftError = leftTarget - leftPos;
                leftDeriv = leftError - lastLeftError;
                lastLeftError = leftDeriv;


                //checks if error is within integrating bounds
                if (abs(leftError) < CHASSIS_UPPER_INTEGRAL_BOUND || abs(leftError) > CHASSIS_LOWER_INTEGRAL_BOUND)
                    leftIntegral += leftError;
                else
                    leftIntegral = 0;

                //caps integral
                if (leftIntegral > CHASSIS_INTEGRAL_CAP)
                    leftIntegral = CHASSIS_INTEGRAL_CAP;
                else if (leftIntegral < -CHASSIS_INTEGRAL_CAP)
                    leftIntegral = -CHASSIS_INTEGRAL_CAP;

                //calcs power
                leftPower = leftError * CHASSIS_KP + leftIntegral * CHASSIS_KI + leftDeriv * CHASSIS_KD;

                //limits to bounds
                if (leftPower > 127)
                    leftPower = 127;
                else if (leftPower < -127)
                    leftPower = -127;

                /*
                RIGHT ARC CALCULATIONS
                */

                rightPos = getRightPos();
                rightError = rightTarget - rightPos;
                rightDeriv = rightError - lastRightError;
                lastRightError = rightDeriv;


                //checks if error is within integrating bounds
                if (abs(rightError) < CHASSIS_UPPER_INTEGRAL_BOUND || abs(rightError) > CHASSIS_LOWER_INTEGRAL_BOUND)
                    rightIntegral += rightError;
                else
                    rightIntegral = 0;

                //caps integral
                if (rightIntegral > CHASSIS_INTEGRAL_CAP)
                    rightIntegral = CHASSIS_INTEGRAL_CAP;
                else if (rightIntegral < -CHASSIS_INTEGRAL_CAP)
                    rightIntegral = -CHASSIS_INTEGRAL_CAP;

                //calcs power
                rightPower = rightError * CHASSIS_KP + rightIntegral * CHASSIS_KI + rightDeriv * CHASSIS_KD;

                //limits to bounds
                if (rightPower > 127)
                    rightPower = 127;
                else if (rightPower < -127)
                    rightPower = -127;

                /*
                LIMITS ARC OUTPUT
                */

                if (leftPower > CHASSIS_MAX)
                    leftPower = CHASSIS_MAX;
                else if (leftPower < -CHASSIS_MAX)
                    leftPower = -CHASSIS_MAX;

                if (rightPower > CHASSIS_MAX)
                    rightPower = CHASSIS_MAX;
                else if (rightPower < -CHASSIS_MAX)
                    rightPower = -CHASSIS_MAX;


                rightPower = returnRightSlew(rightPower);
                leftPower = returnLeftSlew(leftPower);

                if(isArcRight){
                    rightPower = leftPower * arcRatio;
                }
                else{
                    leftPower = rightPower * arcRatio;
                }

                //scale power on smaller arcs


                /*
                SLANT ARC CALCULATIONS
                */

                if(isArcRight){
                    slantDiff = leftPos * arcRatio - rightPos;
                }
                else{
                    slantDiff = leftPos - arcRatio * rightPos;
                }

                slantDeriv = slantDiff - lastSlantDiff;
                lastSlantDiff = slantDiff;

                slantGains = slantDiff * ARC_SLANT_KP + slantDeriv * ARC_SLANT_KD;

                leftPower -= slantGains;
                rightPower += slantGains;


                right(rightPower);
                left(leftPower);



            }

        }
        pros::delay(20);
    }
}
