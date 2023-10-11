#include<cmath>

#include "Header.h"

float b;

void Actual_dimensions(gear& gear1, gear& pinion1,gear& weaker_gear)
{
	gear1.no_of_teeth = (int)(ceil(gear1.diameter / gear1.module));
	pinion1.no_of_teeth = (int)(ceil(pinion1.diameter / pinion1.module));
	weaker_gear.no_of_teeth = (int)(ceil(weaker_gear.diameter / weaker_gear.module));
	b = k * gear1.module;
}


float check_for_stresses(gear weaker_gear)
{
	float stress;
	stress=(float)(tangential_tooth_load / (3.14 * velocity_factor * b * weaker_gear.lewis_form_factor * weaker_gear.module));
	return stress;
}
