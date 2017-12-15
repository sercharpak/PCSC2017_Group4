//
// Created by laptop on 12/15/17.
//

#include "BandPassFrequencyFilter.h"

BandPassFrequencyFilter::BandPassFrequencyFilter(): FrequencyFilter(){
    name="Band pass filter in the Fourier domain.";
    frequencies.push_back(400.0);
    frequencies.push_back(500.0);
}

BandPassFrequencyFilter::BandPassFrequencyFilter(std::vector<double> pFrequencies):FrequencyFilter(pFrequencies){
    name="Band pass filter in the Fourier domain.";
    double min_frequency = pFrequencies[0];
    double max_frequency = pFrequencies[1];
    if (min_frequency > max_frequency){//Check if the values are not in the wrong order...
        int temp (min_frequency);
        min_frequency = max_frequency;
        max_frequency = temp;
    }
    frequencies = std::vector<double>(2);
    frequencies[0] = min_frequency;
    frequencies[1] = max_frequency;
}


std::vector<std::complex<double>> BandPassFrequencyFilter::applyFilter(std::vector<double> pFrequencies,std::vector<std::complex<double>> pFourierTransform){
    double downBound = frequencies[0];
    double upBound = frequencies[1];
    for (int i =0;i<pFrequencies.size();++i){
        double x = pFrequencies[i];
        if(!((x<=upBound) && (x>=downBound))){
            std::complex<double> zeroComplex(0.0,0.0);
            pFourierTransform[i] = zeroComplex;
        }
    }
    return pFourierTransform;
}