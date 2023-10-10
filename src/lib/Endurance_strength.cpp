#include<iostream>

#include "Header.h"

float endurance_strength_func(gear weaker_gear)
{
	float force;
	force = weaker_gear.endurance_strength * b * weaker_gear.form_factor * weaker_gear.module;
	return force;
}
