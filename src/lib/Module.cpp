#include<iostream>
#include<cmath>

#include "Header.h"

float k = 10;

void velocity_func(gear& weaker_gear)					//velocity function
{
	weaker_gear.velocity = (float)((3.14 * weaker_gear.diameter * weaker_gear.speed_in_rpm*pow(10,-3)) / 60);
}

float tangential_tooth_load_func(gear weaker_gear)		    	//torque function
{	
	float tangential_tooth_load;
	tangential_tooth_load = (1000*power*1/weaker_gear.velocity);
	return tangential_tooth_load;
}

float velocity_factor_func(gear weaker_gear)				//velocity factor function
{
	float vel_factor;
	
	if (weaker_gear.velocity <= 8) {
		vel_factor = (float)(3.05 / (3.05 + weaker_gear.velocity));
	}
	else if (weaker_gear.velocity <= 13) {
		vel_factor = (float)(4.58 / (4.58 + weaker_gear.velocity));
	}
	else if (weaker_gear.velocity <= 20) {
		vel_factor = (float)(6.1 / (6.1 + weaker_gear.velocity));
	}
	else if (weaker_gear.velocity <= 20) {
		vel_factor = (float)(5.55 / (5.55 + sqrt(weaker_gear.velocity)));
	}
	else {
		vel_factor = 0;
	}
	return vel_factor;
}

float module_func(gear& weaker_gear)                                	//module function
{
	float m, tangential_tooth_load, vel_factor, Y, design_stress;
	tangential_tooth_load = tangential_tooth_load_func(weaker_gear);
	vel_factor = velocity_factor_func(weaker_gear);
	Y = (float)weaker_gear.form_factor;
	design_stress = (float)weaker_gear.design_stress;


	m = ceil(sqrt(tangential_tooth_load / (design_stress * vel_factor * k * Y)));  //module equation
	return m;
}

