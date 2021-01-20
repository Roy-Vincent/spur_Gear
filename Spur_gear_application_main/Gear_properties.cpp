#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include "Header.h"
void gear_properties(gear& gear1)
{
	int choice;
	std::cout << "Cast steel, 0.2 %C, heat treated   : choice 1" << std::endl;
	std::cout << "Forged steel, 0.3 %C, heat treated : choice 2" << std::endl;
	std::cout << "Steel, C30, heat treated           : choice 3" << std::endl;
	std::cout << "Cast iron, Grade 25                : choice 4" << std::endl;
	std::cin >> choice;

	if (choice > 0 && choice < 5)
	{
		switch (choice)
		{
		case 1:
			gear1.material = "Cast steel, 0.2 %C, heat treated";
			gear1.design_stress = 193.2f;
			gear1.brinell_hardness_no = 250;
			gear1.endurance_strength = 429.0f;
			gear1.youngs_modulus = 2e5;
			break;

		case 2:
			gear1.material = "Forged steel, 0.3 %C, heat treated";
			gear1.design_stress = 220.0f;
			gear1.brinell_hardness_no = 200;
			gear1.endurance_strength = 345.0f;
			gear1.youngs_modulus = 2e5;
			break;

		case 3:
			gear1.material = "Steel, C30, heat treated";
			gear1.design_stress = 220.6f;
			gear1.brinell_hardness_no = 300;
			gear1.endurance_strength = 515.0f;
			gear1.youngs_modulus = 2e5;
			break;
		case 4:
			gear1.material = "Cast iron, Grade 25";
			gear1.design_stress = 56.4f;
			gear1.brinell_hardness_no = 220;
			gear1.endurance_strength = 72;  //this endurance strength is wrong.correct it
			gear1.youngs_modulus = 1e5;
			break;
		}
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::cout << "WRONG INPUT...!";
		exit(0);
	}
}