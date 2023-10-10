#include <iostream>
#include <cmath>

#include "lib/Header.h"

gear Get_weaker_part(gear& GEAR, gear& PINION){
    //Identification of weaker part
	std::cout << "Select choice 1 for 14.5 degree full depth involute system :" << std::endl;
	std::cout << "Select choice 2 for 20 degree full depth involute system   :" << std::endl;
	std::cout << "Select choice 3 for 20 degree stub teeth system            :" << std::endl;
	std::cin >> choice_gear_system;
	if (choice_gear_system > 0 && choice_gear_system < 4)
	{	
		Lewis_form_factor_func(choice_gear_system,GEAR,PINION);
		std::cout << std::endl<<std::endl;
	}
	angle_func(choice_gear_system);


	std::cout << "-------------------------------------------------" << std::endl;

	gear WEAKER_PART = weaker_part(GEAR, PINION);
	std::cout <<"The design is based on "<<' '<<WEAKER_PART.gear_type << std::endl;
	std::cout << "-------------------------------------------------" << std::endl<< std::endl;

    return WEAKER_PART;
}

void Get_module(gear& GEAR, gear& PINION, gear& WEAKER_PART){
    //To find module
	velocity_func(WEAKER_PART);
	tangential_tooth_load = tangential_tooth_load_func(WEAKER_PART);
	velocity_factor = velocity_factor_func(WEAKER_PART);
	torque = (float)(((double)tangential_tooth_load * (double)WEAKER_PART.diameter * pow(10, -3)) / 2);
	std::cout << "Velocity               :" <<' '<< WEAKER_PART.velocity <<" m/s"<< std::endl;
	std::cout << "Tangential tooth load  :" <<' '<< tangential_tooth_load <<" N"<< std::endl;
	std::cout << "Torque                 :" << ' ' << torque <<" Nmm"<< std::endl;
	std::cout << "Velocity factor        :" <<' '<< velocity_factor << std::endl;
	
	module = module_func(WEAKER_PART);
	WEAKER_PART.module = (int)module;
	std::cout << "Module (m)             :" <<' '<< module <<" mm"<< std::endl;

	GEAR.module = PINION.module = WEAKER_PART.module;
	GEAR.velocity = PINION.velocity = WEAKER_PART.velocity;
}

void Get_unknown_dimensions(gear& GEAR, gear& PINION, gear& WEAKER_PART){
    //Determination of unknown dimensions
	float design_stress = 0;
	do {
		Actual_dimensions(GEAR, PINION,WEAKER_PART);
		std::cout << "k                      :" <<' '<< k << std::endl;
		std::cout << "width(b)               :" <<' '<< b <<" mm"<< std::endl<<std::endl;

		design_stress = check_for_stresses(WEAKER_PART);    //Check for stresses

		if (design_stress < WEAKER_PART.design_stress) {
			std::cout << "Design maximum stress  :" <<' '<< design_stress <<" N"<< std::endl;
			std::cout << "The design is safe for the current module..!" << std::endl;
			break;

		}
		else {
			std::cout << "The module needs to be increased..!";
			WEAKER_PART.module += 1;
			GEAR.module = PINION.module = WEAKER_PART.module;
		}
	} while (design_stress > WEAKER_PART.design_stress);
	std::cout << std::endl << std::endl;
}

void Get_dynamic_load(gear& GEAR, gear& PINION){
    //Dynamic load
	dynamic_load = dynamic_load_func(GEAR, PINION);
	std::cout << "DYNAMIC LOAD       :" <<' '<< dynamic_load <<' '<<"N"<<std::endl<<std::endl;
}

void Get_endurance_strength(gear& WEAKER_PART){
    //Endurance strength
	endurance_strength = endurance_strength_func(WEAKER_PART);
	std::cout << "ENDURANCE STRENGTH :" <<' '<< endurance_strength << ' ' << "N" << std::endl;
	
	if (endurance_strength > dynamic_load) {
		std::cout << "The gear is safe against dynamic wear" << std::endl << std::endl;
	}
	else {
		std::cout << "The gear will fail" << std::endl << std::endl;
	}
}

void Get_wear_load(gear& GEAR, gear& PINION, gear& WEAKER_PART){
    //Wear load
	float load_stress_factor,d_gear,Q;
	if (WEAKER_PART.gear_type == "GEAR") {
		load_stress_factor = load_stress_factor_func(WEAKER_PART, PINION);
	}
	else {
		load_stress_factor = load_stress_factor_func(WEAKER_PART, GEAR);
	}

	Q = ratio_factor_func(GEAR, PINION);
	d_gear = GEAR.diameter;
	wear_load = wear_load_func(load_stress_factor, d_gear, Q, b);

	std::cout << "WEAR LOAD          :" <<' '<< wear_load <<' '<<"N"<<std::endl;
	
	if (wear_load > dynamic_load) {
		std::cout << "The gear is safe against wear" << std::endl << std::endl;
	}
	else {
		std::cout << "The gear is subjected to rapid wear and is needed to be surface hardened to a higher BHN" << std::endl << std::endl;
	}
}

void Print_data(gear& GEAR, gear& PINION, gear& WEAKER_PART){
    //print data:
	std::cout << std::endl << std::endl;
	if (WEAKER_PART.gear_type == GEAR.gear_type)
	{
		std::cout << "Dimensions of the weaker part GEAR" << std::endl;
		std::cout << "-------------------------------------------------" << std::endl;
		GEAR.print_gear_data();

		std::cout << "Dimensions of PINION" << std::endl;
		std::cout << "-------------------------------------------------" << std::endl;
		PINION.print_gear_data();
	}
	else {
		std::cout << "Dimensions of the weaker part PINION" << std::endl;
		std::cout << "-------------------------------------------------" <<std::endl;
		PINION.print_gear_data();

		std::cout << "Dimensions of GEAR" << std::endl;
		std::cout << "-------------------------------------------------" << std::endl;
		GEAR.print_gear_data();
	}
}