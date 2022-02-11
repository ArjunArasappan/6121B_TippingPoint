#include "main.h"

pros::Motor intake(INTAKE, MOTOR_GEARSET_06, true, MOTOR_ENCODER_DEGREES);

int intakeMode = 0;

int OP_INTAKE_VEL = 300;

void intakeOpControl() {
  if (master.get_digital(DIGITAL_R2)) {
    intake.move_velocity(OP_INTAKE_VEL);
  }
  else if(master.get_digital(DIGITAL_Y)){
      intake.move_velocity(-OP_INTAKE_VEL);
  }
  else {
    intake.move_velocity(0);
  }

}

void setIntakeMode(int mode){
    intakeMode = mode;
}


void intakeTask(void* parameter) {
    intake.tare_position();
    while(true){
        if(intakeMode == 0){
            intakeOpControl();
        }
        else{

        }

      pros::delay(20);
    }
}
