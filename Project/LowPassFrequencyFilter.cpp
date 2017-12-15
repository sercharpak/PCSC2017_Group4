//
// Created by laptop on 12/15/17.
//

#include "LowPassFrequencyFilter.h"

LowPassFrequencyFilter::LowPassFrequencyFilter(): FrequencyFilter(){
    name="Low pass filter in the Fourier domain.";
    frequencies.push_back(440.0);
}

LowPassFrequencyFilter::LowPassFrequencyFilter(double pFrequency):FrequencyFilter(pFrequency){
    name="Low pass filter in the Fourier domain.";
    frequencies.push_back(pFrequency);
}


std::vector<std::complex<double>> LowPassFrequencyFilter::applyFilter(std::vector<double> pFrequencies,std::vector<std::complex<double>> pFourierTransform){
    std::cout <<"Low pass Filter"<<std::endl;
    double cutFreq = frequencies.back();
    for (int i =0;i<pFrequencies.size();++i){
        double x = pFrequencies[i];
        if(!(x<=cutFreq)){
            std::complex<double> zeroComplex(0.0,0.0);
            pFourierTransform[i] = zeroComplex;
        }
    }
    return pFourierTransform;
}