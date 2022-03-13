#include<iostream>
#include<cmath>
#include<stdlib.h>
#include "Header.h"
float power, vel_ratio, module, tangential_tooth_load, velocity_factor, torque,
	endurance_strength,dynamic_load, wear_load;
int choice_gear_system;
int main()
{	
	gear GEAR;
	gear PINION;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "ENTER YOUR CHOICE FOR GEAR MATERIAL" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	gear_properties(GEAR);
	GEAR.gear_type = "GEAR";

	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "ENTER YOUR CHOICE FOR PINION MATERIAL" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	gear_properties(PINION);
	PINION.gear_type = "PINION";
	std::cout << std::endl << std::endl;
	
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "ENTER THE FOLLOWING DATA" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "Enter the power in Kw              :" << ' ';
	std::cin >> power;									//Power
	std::cout << "enter the velocity ratio           :" << ' ';
	std::cin >> vel_ratio;								//Velocity ratio
	std::cout << std::endl << std::endl;


//Diameter of gear and pinion
	std::cout << "Diameter of either gear or pinion is nessesery...!" << std::endl << std::endl;
	int choice_dia;
	std::cout << "Enter choice 1 to enter gear dia   :" << std::endl;
	std::cout << "Enter choice 2 to enter pinion dia : " << std::endl;
	std::cin >> choice_dia;
	if (choice_dia == 1 || choice_dia == 2)
	{
		if (choice_dia == 1) {
			Dia_teeth(GEAR);
			PINION.diameter = std::ceil(GEAR.diameter / vel_ratio);
		}
		else {
			Dia_teeth(PINION);
			GEAR.diameter = std::ceil(PINION.diameter * vel_ratio);
		}
	}
	else
	{	
		std::cout << "WRONG INPUT...!";
		exit(0);		
	}
	std::cout << std::endl << std::endl;


//Speed of gear and pinion
	std::cout << "Speed of either gear or pinion is nessesery...!" << std::endl << std::endl;
	int choice_speed;
	std::cout << "Enter choice 1 to enter speed of gear   :" << std::endl;
	std::cout << "Enter choice 2 to enter speed of pinion :" << std::endl;
	std::cin >> choice_speed;
	if (choice_speed == 1 || choice_speed == 2)
	{
		if (choice_speed == 1) {
			Speed(GEAR);
			PINION.speed_in_rpm = (int)std::ceil((float)GEAR.speed_in_rpm * vel_ratio);
		}
		else {
			Speed(PINION);
			GEAR.speed_in_rpm = (int)std::ceil((float)PINION.speed_in_rpm / vel_ratio);
		}
	}
	else
	{
		std::cout << "WRONG INPUT...!";
		exit(0);
	}
	std::cout << std::endl << std::endl;


	PINION.no_of_teeth = 20;
	GEAR.no_of_teeth = (int)(ceil(PINION.no_of_teeth * vel_ratio));

//Step:2
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


//step:3
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


//step:4
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
	
//step:5
//Dynamic load
	dynamic_load = dynamic_load_func(GEAR, PINION);
	std::cout << "DYNAMIC LOAD       :" <<' '<< dynamic_load <<' '<<"N"<<std::endl<<std::endl;


//step:6
//Endurance strength
	endurance_strength = endurance_strength_func(WEAKER_PART);
	std::cout << "ENDURANCE STRENGTH :" <<' '<< endurance_strength << ' ' << "N" << std::endl;
	
	if (endurance_strength > dynamic_load) {
		std::cout << "The gear is safe against dynamic wear" << std::endl << std::endl;
	}
	else {
		std::cout << "The gear will fail" << std::endl << std::endl;
	}

//step:7
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

	system("pause>0");
}