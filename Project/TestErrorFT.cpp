//=======================================================================
/** @file TestErrorFT.cpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing.
 *
 * This file is to test if the error handler for the inverse fourier transform is working correctly
 *
 * In order to do that, I generate a signal from a special frequency.
 * Then I apply the inverse Fourier transform and see if the error is throw since the fourier transform wasn't calculated...
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
#include "StandardFilter.h"
#include "MeanFilter.h"
#include "Read.h"


int main(int argc, char* argv[]) {

    //Construct the signal from the frequency 5 and 10000 samples
    ConstructFromFrequency LA_Note(5,10000);
    Signal LA_NoteSignal;
    LA_NoteSignal = LA_Note.construct();

    try {
        //Compute the inverse fourier transform of a signal but the fourier transform wasn't calculated before.
        std::vector<double> ReconstructSample(LA_NoteSignal.inversefourierTransform());

    }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
        return 1;
    }



    return 0;
}
