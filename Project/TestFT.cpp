//=======================================================================
/** @file TestFT.cpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing.
 *
 * This file is to test if the Fourier transform and the inverse one are working correctly
 *
 * In order to do that, I generate a signal from a special frequency and then compute the FT and see if the frequency
 * I used is the only one that is present on the FT.
 * Then I apply the inverse Fourier transform and see if the input signal and the reconstruct one are the same.
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

    //Compute the Fourier transform of the signal
    LA_NoteSignal.FourierTransformCalculator();

    std::vector<double> ReconstructSample(LA_NoteSignal.InverseFourierTransform());

    //Test if the input signal and the reconstruct one are close.

    double error(0);

    for (size_t i(0); i< LA_NoteSignal.getSamples().size(); ++i){
        error += pow(LA_NoteSignal.getSamples()[i]-ReconstructSample[i],2);
    }

    std::cout << "The error is " << error << std::endl;

    // OUTPUT : The error is 1.39112e-20
    


    return 0;
}
