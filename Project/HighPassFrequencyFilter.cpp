//=======================================================================
/** @file HighPassFrequencyFilter.cpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines a High Pass Frequency filter in the Fourier domain.
 *
 */
//=======================================================================

#include "HighPassFrequencyFilter.h"

HighPassFrequencyFilter::HighPassFrequencyFilter(): FrequencyFilter(){
    name="High pass filter in the Fourier domain.";
    frequencies.push_back(440.0);
}

HighPassFrequencyFilter::HighPassFrequencyFilter(double pFrequency):FrequencyFilter(pFrequency){
    name="High pass filter in the Fourier domain.";
    frequencies.push_back(pFrequency);
}


std::vector<std::complex<double>> HighPassFrequencyFilter::applyFilter(std::vector<double> pFrequencies,std::vector<std::complex<double>> pFourierTransform){
    double cutFreq = frequencies.back();
    double x(0.0);
    for (int i =0;i<pFrequencies.size();++i){
        x = pFrequencies[i];
        if(x<cutFreq){
            std::complex<double> zeroComplex(0.0,0.0);
            pFourierTransform[i] = zeroComplex;
        }
    }
    return pFourierTransform;
}