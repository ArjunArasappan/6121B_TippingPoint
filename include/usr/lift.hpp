#ifndef _LIFT_HPP_
#define _LIFT_HPP_

void clamp(bool state);


void setLiftTarget(double target);

void liftPrintInfo();

void clampPiston(bool val);

void setLiftMode(int mode);

void calcDelta();

void liftTask(void *param);



#endif
