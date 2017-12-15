//
// Created by laptop on 12/15/17.
//

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
    for (int i =0;i<pFrequencies.size();++i){
        double x = pFrequencies[i];
        if(!(x>=cutFreq)){
            std::complex<double> zeroComplex(0.0,0.0);
            pFourierTransform[i] = zeroComplex;
        }
    }
    return pFourierTransform;
}