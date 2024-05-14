#!/bin/sh

# Prompt the user for mass
printf "Enter the mass: "
read -r mass

# Prompt the user for acceleration due to gravity
printf "Enter the acceleration due to gravity: "
read -r gravity

# Prompt the user for damping factor
printf "Enter the damping factor: "
read -r damping

# Prompt the user for the length of string
printf "Enter the length of the string: "
read -r length

# Prompt the user for the starting angle
printf "Enter the starting angle: "
read -r angle

# Write the values to dimensions.txt in the TEMP directory
temp_file=/tmp/dimensions.txt

# printf "%s" "$mass " > $temp_file
# printf "%s" "$gravity " >> $temp_file
# printf "%s" "$damping " >> $temp_file
# printf "%s" "$length " >> $temp_file
# printf "%s" "$angle " >> $temp_file

{
    printf "%s" "$mass " ;
    printf "%s" "$gravity ";
    printf "%s" "$damping " ;
    printf "%s" "$length ";
    printf "%s" "$angle ";
} > $temp_file

printf "Dimensions written to %s \n" "$temp_file" 
exit
