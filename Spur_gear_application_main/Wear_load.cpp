#include<iostream>
#include<cmath>
#include "Header.h"

float load_stress_factor_func(gear weaker_gear, gear gear1)
{
	float K;
	K=(float)(((double)pow(weaker_gear.endurance_strength, 2)*(double)sin(angle) / 1.4)* (1 / weaker_gear.youngs_modulus + 1 / gear1.youngs_modulus));
	return K;
}

float ratio_factor_func(gear gear1, gear pinion1)
{
	float Q;
	Q = (float)(2 * gear1.diameter / (gear1.diameter + pinion1.diameter));
	return Q;
}

float wear_load_func(float a, float b, float c, float d) 
{
	return a * b * c * d;
}



