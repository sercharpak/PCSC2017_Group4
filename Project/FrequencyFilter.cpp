//=======================================================================
/** @file FrequencyFilter.cpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines the filtering in the Fourier Domain
 *
 */
//=======================================================================
#include "FrequencyFilter.h"
FrequencyFilter::FrequencyFilter()
{
    name="Frequency filter in the Fourier domain.";
    frequencies.push_back(440.0);
}
FrequencyFilter::FrequencyFilter(double pFrequency)
{
    name="Frequency filter in the Fourier domain.";
    frequencies.push_back(pFrequency);
}
FrequencyFilter::FrequencyFilter(std::vector<double> pFrequencies)
{
    frequencies=pFrequencies;
    name="Frequency filter in the Fourier domain.";
}

std::vector<double> FrequencyFilter::getFrequencies()
{
    return frequencies;
}

std::string FrequencyFilter::getName()
{
    return name;
}

std::vector<std::complex<double>> FrequencyFilter::applyFilter(std::vector<double> pFrequencies,std::vector<std::complex<double>> pFourierTransform){
    double cutFreq = frequencies.back();
    double epsilon = 10.0; // Epsilon quite big because of the small "lag" in the fourier transform
    double upBound = cutFreq+epsilon;
    double downBound = cutFreq-epsilon;

    for (int i =0;i<pFrequencies.size();++i){
        double x = pFrequencies[i];
        if(!((x<=upBound) && (x>=downBound))){
            std::complex<double> zeroComplex(0.0,0.0);
            pFourierTransform[i] = zeroComplex;
        }
    }
    return pFourierTransform;
}

Signal FrequencyFilter::apply(Signal pSignal)
{
    if ((frequencies.empty())||(frequencies.size()>2)){
        throw FourierFilterException();
    }
    std::vector<double> frequenciesInput = pSignal.getFrequencies();
    std::vector<std::complex<double>> fourierTransform = pSignal.getFourierTransform();
    std::vector<std::complex<double>> outFourierTransform = applyFilter(frequenciesInput,fourierTransform);
    Signal outputSignal;
    outputSignal.setFourierTransform(outFourierTransform);
    outputSignal.setFrequencies(frequenciesInput);
    return outputSignal;
}