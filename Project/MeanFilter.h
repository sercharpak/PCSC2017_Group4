//
// Created by shernand on 12/4/17.
//
//=======================================================================
/** @file MeanFilter.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines a mean filter in the spatial domain.
 *
 */
//=======================================================================
#ifndef PROJECT_MEANFILTER_H
#define PROJECT_MEANFILTER_H
/** Class which defines a mean filter in the spatial domain.
 * It is a low pass filter.
 * Example 5 mask: (1/5) [1 1 1 1 1]
 */
#include "StandardFilter.h"
#include <vector>
template <class T>
class MeanFilter : public StandardFilter<T>{
public:
    /** Standard Constructor
     *  The length is set to 5
     *  We construct an array of length 5 with all the entries set as 1/length
     */
    MeanFilter();
    /** Constructor with the length of the mask
     *  We construct an array of given length with all the entries set as 1/length
     * @param pLength int which indicated the length of the filter
     */
    MeanFilter(int pLength);
};

#include "MeanFilter_imp.h"

#endif //PROJECT_MEANFILTER_H
