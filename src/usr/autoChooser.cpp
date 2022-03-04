/*
Credit to VRC Team 315G for most of this code
*/

#include "main.h"

int autonNumber;
int driverState;

static const char *btnm_map[] = {"R1", "L1", "R2", "L2", "\n",
				 				 "SoloAWP", "R_Rush", "L_Rush", "RMid_Rush", ""};
static const char *auton_strings[] = {"R1", "L1", "R2", "L2", "SoloAWP", "R_Rush", "L_Rush", "RMid_Rush", ""};
static const char *alliance_map[] = {"Driver", "Prog", " "};

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

static lv_res_t btnm_action_color(lv_obj_t *btnm, const char *txt){
	lv_btnm_set_toggle(btnm, true, 1);
	lv_btnm_set_toggle(btnm, true, 2);

	if (strcmp(txt, "Driver") == 0){
		driverState = 0;
	}
	else if (strcmp(txt, "Prog") == 1){
		driverState = 1;
	}
	else{
		driverState = 2;
	}

	return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

void autonomousChooserPrintInfo(void *param){
	while (true){
		printf("%d %d\n", autonNumber, driverState);
		pros::delay(20);
	}
}

void autonomousChooserInit(){
	lv_theme_alien_init(40, NULL);

	lv_obj_t *title = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(title, "6121B Auto Sauce");
	lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

	lv_obj_t *btnm = lv_btnm_create(lv_scr_act(), NULL);
	lv_btnm_set_map(btnm, btnm_map);
	lv_btnm_set_action(btnm, btnm_action);
	lv_obj_set_size(btnm, LV_HOR_RES - 40, LV_VER_RES / 3);
	lv_obj_align(btnm, title, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

	lv_obj_t *allianceM = lv_btnm_create(lv_scr_act(), NULL);
	lv_btnm_set_map(allianceM, alliance_map);
	lv_btnm_set_action(allianceM, btnm_action_color);
	lv_obj_set_size(allianceM, LV_HOR_RES - 40, 50);
	lv_obj_align(allianceM, btnm, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
}

bool autonomousChooserGetdriverState(){

	return driverState;
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
			progSkills();
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		default:
			break;
	}

	if(driverState == 0){
	}
	else if (driverState == 1){
		progSkills();
	}
}
