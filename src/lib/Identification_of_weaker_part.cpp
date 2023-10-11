#include<iostream>

#include "Header.h"

void Lewis_form_factor_func(int x,gear& gear1, gear& pinion1)
{	
	switch (x)
	{
	case 1:									// 14.5 degree full depth involute system
		gear1.lewis_form_factor = (float)(0.124 - (0.684 / gear1.no_of_teeth));
		pinion1.lewis_form_factor = (float)(0.124 - (0.684 / pinion1.no_of_teeth));
		gear1.form_factor = (float)(gear1.lewis_form_factor * 3.14);
		pinion1.form_factor = (float)(pinion1.lewis_form_factor * 3.14);
		break;
	
	case 2:                                 				// 20 degree full depth involute system
		gear1.lewis_form_factor = (float)(0.154 - (0.912 / gear1.no_of_teeth));
		pinion1.lewis_form_factor = (float)(0.154 - (0.912 / pinion1.no_of_teeth));
		gear1.form_factor = (float)(gear1.lewis_form_factor * 3.14);
		pinion1.form_factor = (float)(pinion1.lewis_form_factor * 3.14);
		break;
	
	case 3:                                 				// 20 degree stub teeth system
		gear1.lewis_form_factor = (float)(0.175 - (0.95 / gear1.no_of_teeth));
		pinion1.lewis_form_factor = (float)(0.175 - (0.95 / pinion1.no_of_teeth));
		gear1.form_factor = (float)(gear1.lewis_form_factor * 3.14);
		pinion1.form_factor = (float)(pinion1.lewis_form_factor * 3.14);
		break;
	
	default:
		gear1.lewis_form_factor = 0;
		pinion1.lewis_form_factor = 0;
		gear1.form_factor = 0;
		pinion1.form_factor = 0;
	}
}

gear weaker_part(gear& gear1, gear& pinion1)       //Weaker part identification
{	
	gear weaker_gear;
	if (gear1.material == pinion1.material) {
		weaker_gear = pinion1;
	}
	else if ((gear1.design_stress * gear1.lewis_form_factor) > (pinion1.design_stress * pinion1.lewis_form_factor)) {
		weaker_gear = pinion1;
	}
	else {
		weaker_gear = gear1;
	}
	return weaker_gear;
}
