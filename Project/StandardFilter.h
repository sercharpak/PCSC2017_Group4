//
// Created by Sergio Daniel Hernandez on 12/3/17.
//
//=======================================================================
/** @file StandardFilter.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines a standard filter in the spatial domain.
 *
 */
//=======================================================================
#ifndef PCSC2017_GROUP4_STANDARDFILTER_H
#define PCSC2017_GROUP4_STANDARDFILTER_H
/** Class which defines a standard filter in the spatial domain.
 */
#include <math.h>
#include <string>
#include <vector>
#include "Signal.h"
#include "FilterSizeException.hpp"
template <class T>
class StandardFilter {
protected:
    /** Numerator coefficients of the mask of the filter.
     */
    std::vector<T> mask;
    /** Length of the mask of the filter
    */
    int length;
    /** name of the filter
    */
    std::string name;
public:
    /** Standard Constructor
     * The length is set to 5
     */
    StandardFilter();
    /** Constructor with the length of the mask
     * @param pLength int which indicated the length of the filter
     */
    StandardFilter(int pLength);
    /** Constructor with the mask
     * @param pMask std::vector<T> which defines the filter
     */
    StandardFilter(std::vector<T> pMask);
    /** Destructor
     */
     ~StandardFilter();
    /** Sets a 1D mask given by parameter
     * @param std::vector<T> the mask to be set
     */
    void setMask(std::vector<T> pMask);
    /** Gives the 1D mask of the filter
     * @return std::vector<T> the mask of the filter
     */
    std::vector<T> getMask();
    /** Sets the length of the mask
     * @param int the length to be set
     */
    void setLength(int pLength);
    /** Gives the length of the 1D filter
     * @return int the length of the filter
     */
    int getLength();
    /** Sets the name of the filter
     * @param std::string the name to be set
     */
    void setName(std::string pName);
    /** Gives the name of the 1D filter
     * @return std::string the name of the filter
     */
    std::string getName();
    /** Applies the filter to the raw data of a signal
     * @param std::vector<T> the raw data to which we want to apply the filter.
     * @return std::vector<T> the raw data filtered
     */
    std::vector<T> apply(std::vector<T> pSignal);
    /** Applies the filter to the signal object
     * @param Signal the signal to which we want to apply the filter.
     * @return New Signal object with the data filtered
     */
    Signal apply(Signal pSignal);

};

#include "StandardFilter_imp.h"


#endif //PCSC2017_GROUP4_STANDARDFILTER_H
