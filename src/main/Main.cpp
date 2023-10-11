#include "../lib/Header.h"

float power, vel_ratio, module, tangential_tooth_load, velocity_factor, torque, endurance_strength,dynamic_load, wear_load;
int choice_gear_system;

int main()
{	
	gear GEAR, PINION, WEAKER_PART;

	//step:1
	get_gear_material(GEAR,"GEAR");
	get_gear_material(PINION, "PINION");	
	get_power_and_vel_ratio();
	get_dia_gear_or_pinion(GEAR, PINION);
	get_speed_gear_or_pinion(GEAR, PINION);

	//step:2
	WEAKER_PART = Get_weaker_part(GEAR, PINION);

	//step:3
	Get_module(GEAR, PINION, WEAKER_PART);

	//step:4
	Get_unknown_dimensions(GEAR, PINION, WEAKER_PART);
	
	//step:5
	Get_dynamic_load(GEAR, PINION);

	//step:6
	Get_endurance_strength(WEAKER_PART);

	//step:7
	Get_wear_load(GEAR, PINION, WEAKER_PART);

	Print_data(GEAR, PINION, WEAKER_PART);

}
