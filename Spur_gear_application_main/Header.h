#pragma once
#include<iostream>
#include<string>
extern float power, vel_ratio;		 //power and velocity ratio
								    
extern int choice_gear_system; 

extern float k,b,module;			//unknown variables

extern float tangential_tooth_load,endurance_strength,wear_load,dynamic_load;

extern float velocity_factor, torque;

extern float angle;

class gear							// gear class to create GEAR and PINION
{
public:
	int module;
	int no_of_teeth;
	int speed_in_rpm;
	int brinell_hardness_no;
	float velocity;
	float diameter;
	float lewis_form_factor;
	float form_factor;
	float design_stress;
	float endurance_strength;
	double youngs_modulus;
	std::string material;
	std::string gear_type;

	gear()
	{
		module = 0;
		no_of_teeth = 0;
		brinell_hardness_no = 0;
		velocity = 0;
		diameter = 0;
		design_stress = 0.0f;
		endurance_strength = 0.0f;
		material = "MATERIAL";
		gear_type = "USER DEFINED";
		lewis_form_factor = 0;
		form_factor = 0;
		youngs_modulus = 0.0f;
	}

	void print_gear_data()
	{
		std::cout << "Module                        :" << ' ' << module << ' ' << "mm" << std::endl;
		std::cout << "Number of teeth               :" << ' ' << no_of_teeth << std::endl;
		std::cout << "Speed in rpm                  :" << ' ' << speed_in_rpm << "rpm" << std::endl;
		std::cout << "Brinell Hardness Number (BHN) :" << ' ' << brinell_hardness_no << std::endl;
		std::cout << "Velocity                      :" << ' ' << velocity <<' '<<"m/s"<< std::endl;
		std::cout << "Diameter                      :" << ' ' << diameter << ' ' << "mm" << std::endl;
		std::cout << "Design stress                 :" << ' ' << design_stress << ' ' << "MPa" << std::endl;
		std::cout << "Endurance strength            :" << ' ' << endurance_strength << ' ' << "MPa" << std::endl;
		std::cout << "Material                      :" << ' ' << material << std::endl;
		std::cout << "Gear type                     :" << ' ' << gear_type << std::endl;
		std::cout << "Lewis form factor             :" << ' ' << lewis_form_factor << std::endl;
		std::cout << "Form factor                   :" << ' ' << form_factor << std::endl;
		std::cout << "Young's modulus               :" << ' ' << youngs_modulus <<' '<<"N/mm2"<< std::endl;
		std::cout << std::endl;
	}
};

void gear_properties(gear& gear1);

float angle_func(int choice);

void Dia_teeth(gear& x);

void Speed(gear& x);

void Lewis_form_factor_func(int x,gear& gear1,gear& pinion1);

gear weaker_part(gear& gear1, gear& pinion1);

float tangential_tooth_load_func(gear weaker_gear);

float velocity_factor_func(gear weaker_gear);

float module_func(gear& weaker_gear);

void velocity_func(gear& weaker_gear);

void Actual_dimensions(gear& gear1, gear& pinion1, gear& weaker_gear);

float check_for_stresses(gear weaker_gear);


//Dynamic tooth load
float func_k1();
float error_function(gear weaker_gear);
double dynamic_factor_func(gear gear1, gear pinion1);
float dynamic_load_func(gear gear1, gear pinion1);


//Endurance strength
float endurance_strength_func(gear weaker_gear);


//wear load
float load_stress_factor_func(gear weaker_gear, gear gear1);
float ratio_factor_func(gear gear1, gear pinion1);
float wear_load_func(float a, float b, float c, float d);