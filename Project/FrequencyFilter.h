//
// Created by shernand on 12/7/17.
//
//=======================================================================
/** @file FrequencyFilter.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines a Standard Frequency filter in the Fourier domain.
 *
 */
//=======================================================================
#ifndef PROJECT_FREQUENCYFILTER_H
#define PROJECT_FREQUENCYFILTER_H
/** Class which defines a standard filter in the fourier domain.
 */
#include <vector>
#include <algorithm>
#include <string>
#include <vector>
#include "FilterSizeException.hpp"
#include "Signal.h"
#include "FourierFilterException.hpp"
class FrequencyFilter{
protected:
/** Cut frequencies.
 */
std::vector<double> frequencies;

/** name of the filter
*/
std::string name;
public:
    /** Standard Constructor
     * Sets the cut frequency to 440 (LA)
     */
    FrequencyFilter();
    /** Constructor with one frequency for the cut
     * @param pFrecuency double which indicates the cut frequency
     */
    FrequencyFilter(double pFrecuency);
    /** Constructor with several frequencies for the cut
     * @param pFrecuencies std::vector<double> which indicates the frequencies relevant to the filter.
     */
    FrequencyFilter(std::vector<double> pFrecuencies);
    /** Gives the length of the 1D filter
     * @return std::vector<double> the frequencies of the filter
     */
    std::vector<double> getFrequencies();
    /** Gives the name of the 1D filter
     * @return std::string the name of the filter
     */
    std::string getName();
    /** Applies the filter to the frequency data of a signal
     * By default it is a only one frequency pass filter (a band pass around a frequency with an epsilon)
     * @param std::vector<double> the frequency data to which we want to apply the filter.
     * @param std::vector<std::complex<double>> pFourierTransform the fourier data to be filtered.
     * @return std::vector<std::complex<double>> the fourier data filtered
     */
    virtual std::vector<std::complex<double>> applyFilter(std::vector<double> pFrequencies,std::vector<std::complex<double>> pFourierTransform);
        /** Applies the filter to the signal object
         * @param Signal the signal to which we want to apply the filter.
         * @return New Signal object with the data filtered
         */
    Signal apply(Signal pSignal);
};


#endif //PROJECT_FREQUENCYFILTER_H
