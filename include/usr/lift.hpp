#ifndef _LIFT_HPP_
#define _LIFT_HPP_

void clamp(bool state);

void setGoal(bool state);

void setLiftTarget(double target);

void liftPrintInfo();

void clampPiston(bool val);

void setLiftMode(int mode);

void calcDelta();

void tareLift();

void liftDelay();

void liftTask(void *param);


const int LIFT_PLAT = 700;
const int LIFT_LOW_PLAT = 460;



#endif
