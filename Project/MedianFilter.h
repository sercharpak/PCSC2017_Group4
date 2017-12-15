//
// Created by shernand on 12/7/17.
//
//=======================================================================
/** @file MedianFilter.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines a median filter in the spatial domain. Very useful to remove impulse noise.
 *
 */
//=======================================================================
#ifndef PROJECT_MEDIANFILTER_H
#define PROJECT_MEDIANFILTER_H
/** Class which defines a  median filter in the spatial domain.
 * It is a NON linear filter
 * Very useful to remove impulse noise
 */
#include <vector>
#include <algorithm>
#include <string>
#include <vector>
#include "FilterSizeException.hpp"
#include "Signal.h"
class MedianFilter{
protected:
/** Numerator coefficients of the mask of the filter.
 */
std::vector<double> mask;
/** Length of the mask of the filter
*/
int length;
/** name of the filter
*/
std::string name;
public:
    /** Standard Constructor
     *  The length is set to 5
     *  We compute the median with a 5 sized window.
     */
    MedianFilter();
    /** Constructor with the length of the mask
     *  We compute the median with a 5 sized window.
     * @param pLength int which indicated the length of the filter
     */
    MedianFilter(int pLength);
    /** Gives the length of the 1D filter
     * @return int the length of the filter
     */
    int getLength();
    /** Gives the name of the 1D filter
     * @return std::string the name of the filter
     */
    std::string getName();
    /** Applies the filter to the raw data of a signal
     * Computes the median (non linear operation)
     * @param std::vector<T> the raw data to which we want to apply the filter.
     * @return std::vector<T> the raw data filtered
     */
    std::vector<double> applySamples(std::vector<double> pSignal);
    /** Applies the filter to the signal object
     * @param Signal the signal to which we want to apply the filter.
     * @return New Signal object with the data filtered
     */
    Signal apply(Signal pSignal);
};


#endif //PROJECT_MEDIANFILTER_H
