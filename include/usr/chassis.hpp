#ifndef _CHASSIS_HPP_
#define _CHASSIS_HPP_

void setChassisMode(int mode);

void _leftReset();
void _rightReset();

void chassisTask(void *);

void setBrakeMode(int mode);

void setChassisMax(int power);
void setChassisAccel(int step);

void setTurnMax(int power);
void setTurnAccel(int step);

void leftWaitUntilSettled();
void rightWaitUntilSettled();

void turnWaitUntilSettled();

void chassisWaitUntilSettled();

void moveForward(double distance_inches);
void moveForwardAsync(double distance_inches);

void moveBack(double distance_inches);
void moveBackAsync(double distance_inches);

void turn(double degrees);
void turnAsync(double degrees);

void leftMove(double iTarget);
void leftMoveAsync(double iTarget);
void rightMove(double iTarget);
void rightMoveAsync(double iTarget);

void pointTurnAsync(bool isRight, double angle);

void pointTurn(bool isRight, double angle);

void arcTurnAsync(double rad, double angle);
void arcTurn(double rad, double angle);




#endif
