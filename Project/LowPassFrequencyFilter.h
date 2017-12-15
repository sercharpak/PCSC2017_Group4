//
// Created by laptop on 12/15/17.
//
//=======================================================================
/** @file HighPassFrequencyFilter.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines a High Pass Frequency filter in the Fourier domain.
 *
 */
//=======================================================================
#ifndef PROJECT_LOWPASSFREQUENCYFILTER_H
#define PROJECT_LOWPASSFREQUENCYFILTER_H
/** Class which defines a high pass filter in the fourier domain.
 * Applies a LowPass Frequency. All the frequencies less than the frequency given are set to 0.
 */
#include "FrequencyFilter.h"
class LowPassFrequencyFilter : public FrequencyFilter{
public:
    /** Standard Constructor
     * Sets the cut frequency to 440 (LA)
     */
    LowPassFrequencyFilter();
    /** Constructor with one frequency for the cut
     * @param pFrecuency double which indicates the cut frequency
     */
    LowPassFrequencyFilter(double pFrecuency);
    /** Applies the filter to the frequency data of a signal
     * Applies a LowPass Frequency. All the fourier data less than the frequency given are set to 0.
     * @param std::vector<double> the frequency data to which we want to apply the filter.
     * @param std::vector<std::complex<double>> pFourierTransform the fourier data to be filtered.
     * @return std::vector<std::complex<double>> the fourier data filtered
     */
    virtual std::vector<std::complex<double>> applyFilter(std::vector<double> pFrequencies,std::vector<std::complex<double>> pFourierTransform) override;

};


#endif //PROJECT_LOWPASSFREQUENCYFILTER_H
