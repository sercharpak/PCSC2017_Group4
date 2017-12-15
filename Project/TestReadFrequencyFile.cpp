//=======================================================================
/** @file TestReadFrequencyFile.cpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing.
 *
 * This file is to test if the creation of a signal from a frequency file is working correctly.
 *
 * In order to do that, I open a file containing 3 different frequencies.
 * Then I read this file and construct the signal out of it.
 *
 *
*/
//=======================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <complex>

#include "AudioFile.h"
#include "Signal.h"
#include "Read.h"

int main(int argc, char* argv[]) {

    std::string name("frequencyFile.dat");

    //Create the file with some frequencies
    std::ofstream File(name);
    File << "20 440 500 ";
    File.close();

    //Create the signal from the frequency file
    ReadFrequencyFile FileFrequency (name,10000);

    Signal SignalFrequency= FileFrequency.construct();

    //Check if the frequencies are at the right place
    SignalFrequency.writeFourier("FileFrequencyTest.dat");

    //I plot the result in gnuplot in order to see where are the frequencies, and they are at the right place.


    return 0;
}