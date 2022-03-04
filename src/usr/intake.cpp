#include "main.h"

pros::Motor intake(INTAKE, MOTOR_GEARSET_06, false, MOTOR_ENCODER_DEGREES);

int intakeMode = 1;

int OP_INTAKE_VEL = 450;

int autoIntakeVel = 0;

bool isDriverIntake = false;

void intakeOpControl() {
  if (master.get_digital(DIGITAL_R2)) {
    intake.move_velocity(OP_INTAKE_VEL);
  }
  else if(master.get_digital(DIGITAL_DOWN)){
      intake.move_velocity(-OP_INTAKE_VEL);
  }
  else {
    intake.move_velocity(0);
  }

  if(isDriverIntake && driver_isLiftPast){
      intake.move_velocity(OP_INTAKE_VEL);
  }

}

void setDriverIntake(bool state){
    isDriverIntake = state;
}

void setIntakeMode(int mode){
    intakeMode = mode;
}

void setIntakeVel(int vel){
    autoIntakeVel = vel;
}

void setIntake(bool state){
    if(state)
        autoIntakeVel = OP_INTAKE_VEL;
    else
        autoIntakeVel = 0;
}


void intakeTask(void* parameter) {
    intake.tare_position();
    while(true){
        if(intakeMode == 0){
            intakeOpControl();
        }
        else{
            intake.move_velocity(autoIntakeVel);
        }

      pros::delay(20);
    }
}
