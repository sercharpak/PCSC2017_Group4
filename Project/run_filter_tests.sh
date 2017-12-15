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
## Runs the Fourier domain filter tests
echo "Running the Fourier domain filter tests"
./TestFourierFilters
echo "Fourier domain filter tests ran succesfully"
##Runs the Song Test
echo "Running Test Song"
./TestSong
echo "Test Song ran succesfully"
##Runs the Fourier Transform error test
echo "Running Fourier Transform error test"
./TestErrorFT
echo "Fourier Transform error test ran succesfully"
##Runs the histogram error test
echo "Running Histogram error test"
./TestErrorHistogram
echo "Histogram error test ran succesfully"
##Runs the Fourier Transform test
echo "Running Fourier Transform test"
./TestFT
echo "Fourier Transform test ran succesfully"
##Runs the Fourier Transform test
echo "Running test for reading the frequency file"
./TestFrequencyFile
echo "Test for reading the frequency file ran succesfully"
##Runs the histogram test
echo "Running Histogram test"
./TestHistogram
echo "Histogram test ran succesfully"

