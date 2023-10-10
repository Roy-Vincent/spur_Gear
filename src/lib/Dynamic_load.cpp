#include<cmath>

#include "Header.h"

float func_k1()
{
	float k1=0.0f;
	switch (choice_gear_system)
	{
	case 1:
		k1 = (float)9.345;
		break;
	case 2:
		k1 = (float)9.00;
		break;
	case 3:
		k1 = (float)8.70;
		break;
	default:
		k = 0;
	}
	return k1;
}


float error_function(gear weaker_gear)
{
	float error;
	float velocity = weaker_gear.velocity;
	int vel = (int)(ceil(velocity));
	if (vel == 1)
		error = (float)0.0960;
	else if (vel == 2)
		error = (float)0.0880;
	else if (vel == 3)
		error = (float)0.0785;
	else if (vel == 4)
		error = (float)0.0710;
	else if (vel == 5)
		error = (float)0.0640;
	else if (vel == 6)
		error = (float)0.0590;
	else if (vel <= 8)
		error = (float)0.0500;
	else if (vel <= 10)
		error = (float)0.0386;
	else if (vel <= 12)
		error = (float)0.0330;
	else if (vel <= 15)
		error = (float)0.0230;
	else if (vel <= 20)
		error = (float)0.0155;
	else
		error = 0;

	return error;
}


double dynamic_factor_func(gear gear1,gear pinion1)
{
	double C;
	double error = error_function(gear1);
	double k1 = func_k1();
	double E1 = gear1.youngs_modulus;
	double E2 = pinion1.youngs_modulus;
	C = error / (k1 * ((1/E1) + (1/E2)));
	return C;
}


float dynamic_load_func(gear gear1,gear pinion1)
{
	float dynamic_load;
	float k3 = (float)20.67;                             //constant
	float velocity = gear1.velocity;
	float C = (float)(dynamic_factor_func(gear1, pinion1));
	float Fi = (float)(k3 * velocity * (C * b + tangential_tooth_load) / (k3 * velocity + sqrt(C * b + tangential_tooth_load)));
	dynamic_load = tangential_tooth_load + Fi;
	return dynamic_load;
}
