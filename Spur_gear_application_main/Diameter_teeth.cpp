#include<iostream>
#include "Header.h"
float angle;
void Dia_teeth(gear& x)
{
	std::cout << "enter dia :" << ' ';
	std::cin >> x.diameter;

}

void Speed(gear& x)
{
	std::cout << "enter the speed in rpm :" << ' ';
	std::cin >> x.speed_in_rpm;
}

float angle_func(int choice)
{
	switch (choice)
	{
	case 1:
		angle = 14.5;
		break;
	case 2:
		angle = 20;
		break;
	case 3:
		angle = 20;
		break;
	}
	return angle;
}