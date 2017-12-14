#!/usr/bin/env bash
#Folder where the Executable is located.
EXE_FOLDER='./'
#Name of the main executable
EXE='Project'
#Test_audio_folder
TEST_FILES_FOLDER='./test-audio/'

#Goes to the EXE folder
cd ${EXE_FOLDER}

##Runs the Median test
echo "Runing Median test"
./Project ${TEST_FILES_FOLDER}/test_median_options.txt
echo "Median test ran succesfully"
##Runs the Mean (low pass) test
echo "Runing Mean (low pass) test"
./Project ${TEST_FILES_FOLDER}/test_mean_lowPass_options.txt
echo "Mean (low pass) test ran succesfully"
##Runs the Laplace (high pass) test
echo "Runing Laplace (high pass) test"
./Project ${TEST_FILES_FOLDER}/test_laplace_highPass_options.txt
echo "Laplace (high pass) test ran succesfully"
##Runs the Prewitt (band pass) test
echo "Runing Prewitt (band pass) test"
./Project ${TEST_FILES_FOLDER}/test_prewitt_bandPass_options.txt
echo "Prewitt (band pass) test ran succesfully"