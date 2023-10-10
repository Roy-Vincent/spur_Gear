#include <iostream>
#include <cmath>

#include "Header.h"

void get_gear_material(gear& GEAR, std::string GEAR_str){
	std::cout << "-------------------------------------------------" << std::endl;
        std::cout << "ENTER YOUR CHOICE FOR "<<GEAR_str<<" MATERIAL" << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;
        gear_properties(GEAR);
        GEAR.gear_type = GEAR_str;
}


void get_power_and_vel_ratio(){
	std::cout << "-------------------------------------------------" << std::endl;
        std::cout << "ENTER THE FOLLOWING DATA" << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;
        std::cout << "Enter the power in Kw              :" << ' ';
        std::cin >> power;                                                                      //Power
        std::cout << "enter the velocity ratio           :" << ' ';
        std::cin >> vel_ratio;                                                          //Velocity ratio
        std::cout << std::endl << std::endl;
}


//Diameter of gear or pinion
void get_dia_gear_or_pinion(gear& GEAR, gear& PINION){
        std::cout << "Diameter of either gear or pinion is nessacery (dimension in mm)" << std::endl << std::endl;
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
}


//Speed of gear or pinion
void get_speed_gear_or_pinion(gear& GEAR, gear& PINION){
        std::cout << "Speed of either gear or pinion is nessesery (speed in rpm)" << std::endl << std::endl;
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
}
