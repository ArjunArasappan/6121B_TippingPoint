/*
Credit to VRC Team 315G for most of this code
*/

#include "main.h"

int autonNumber;
int driverState;

static const char *btnm_map[] = {"R_Both", "L_Both", "R_Neuts", "L_Neuts", "\n",
								 "AWP", "R_Rush", "L_Rush", "R_MidRush", "\n",
								 "DriverSkills", "ProgSkills", ""};
static const char *auton_strings[] = {"R.Both", "L.Both", "R.Neuts", "L.Neuts", "AWP", "R.Rsh", "L.Rsh", "R.MidRush", "DrivSkills", "ProgSkills"};

static lv_res_t btnm_action(lv_obj_t *btnm, const char *txt){
	for (int i = 0; i < sizeof(auton_strings) / sizeof(auton_strings[0]); i++){
		if (strcmp(auton_strings[i], txt) == 0){
			autonNumber = i + 1;
			break;
		}
		lv_btnm_set_toggle(btnm, true, autonNumber);
	}

	return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}


void autonomousChooserInit(){
	lv_theme_alien_init(40, NULL);

	lv_obj_t *title = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(title, "6121B Auto Sauce");
	lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

	lv_obj_t *btnm = lv_btnm_create(lv_scr_act(), NULL);
	lv_btnm_set_map(btnm, btnm_map);
	lv_btnm_set_action(btnm, btnm_action);
	lv_obj_set_size(btnm, LV_HOR_RES - 20, LV_VER_RES / 2);
	lv_obj_align(btnm, title, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
}

void autonomousChooserExecuteAuto(){

	switch (autonNumber){
		case 1:
			rightBoth();
			break;
		case 2:
			leftBoth();
			break;
		case 3:
			rightNeutrals();
			break;
		case 4:
			leftNeutrals();
			break;
		case 5:
			soloAWP();
			break;
		case 6:
			rightRush();
			break;
		case 7:
			leftRush();
			break;
		case 8:
			rightMidRush();
			break;
		case 9:
			setDriverIntake(true);
			break;
		case 10:
			progSkills();
		default:
			break;
	}
}
