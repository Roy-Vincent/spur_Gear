#!/bin/bash

mkdir ./bin

g++ -o bin/Gear lib/Header.h lib/Actual_dimensions.cpp lib/Diameter_teeth.cpp lib/Dynamic_load.cpp lib/Endurance_strength.cpp \
	lib/Gear_properties.cpp lib/Identification_of_weaker_part.cpp lib/Module.cpp lib/Wear_load.cpp lib/Get_functions.cpp \
	main/do_calc.cpp main/Main.cpp

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    # Open a new terminal tab and execute the compiled program
    gnome-terminal -- bash -c "./bin/Gear; exec bash"
else
    echo "Compilation failed."
fi
