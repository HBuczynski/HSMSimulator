#!/bin/bash

# Set basic variables:
input=$1
target_folder_name="target"

# Create basic target folder.
if [ ! -d $target_folder_name ]; then
    mkdir $target_folder_name
fi

if [ "$input" == "AlexaSim" ]; then

    echo " "
    echo "Building AlexaSIm application."
    echo " "
    # Create build and binary files
    cmake -DTARGET_APP="AlexaSim" . -B"${target_folder_name}"/build
    cmake --build "${target_folder_name}"/build

elif [ "$input" == "HSMExample" ]; then

    echo " "
    echo "Building HSMExample application."
    echo " "
    # Create build and binary files
    cmake -DTARGET_APP="HSMExample" . -B"${target_folder_name}"/build
    cmake --build "${target_folder_name}"/build

elif [ "$input" == "clean" ]; then
    rm -r "${target_folder_name}"/

else
	echo "#################################################################"
    echo " "
	echo -------------------------  HELP  --------------------------------
	echo ---            Available commands:           
	echo ---------------------------------------------------------------
    echo " "
    echo "   --- # AlexaSim       :   Runs Alexa Simulator application.  " 
    echo "   --- # HSMExample     :   Runs basic example of HSM usage." 
	echo "   --- # clean          :   Removes target directory."
    echo " "
    echo -e "\033[32m !! Note: Write appropriate command as input argument to the script."
    echo -e "\033[0m"
	echo "#################################################################"
fi


