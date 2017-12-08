//
// Created by didier on 07/12/17.
//

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

/*This file is to test if the Fourier transform is working correctly
 *
 * In order to do that, I generate a signal from a special frequency and then compute the FT and see if the frequency
 * I used is the only one that is present on the FT.
 *
*/


int main(int argc, char* argv[]) {

    //Construct the signal from the frequency 440
    ConstructFromFrequency LA_Note(440);
    Signal LA_NoteSignal;
    LA_NoteSignal = LA_Note.construct();

    //Compute the Fourier transform of the signal
    LA_NoteSignal.FourierTransformCalculator(-500,500);

    //Test if the only frequency that we found is the 440 frequency.

    for (size_t i(0); i< LA_NoteSignal.getFourierTransform().size(); ++i){
        if (std::abs(LA_NoteSignal.getFourierTransform()[i]) > pow(10.0,-11.0)){
            //I test what are the frequencies for which the modulus is negligeable
            std::cout << "The frequency " << LA_NoteSignal.getFrequencies()[i] << " is non-zero" << std::endl;
        }
    }

    /* OUTPUT : The frequency -440 is non-zero
                The frequency 440 is non-zero
    */


    return 0;
}
