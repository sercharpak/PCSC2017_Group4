//
// Created by shernand on 12/7/17.
//
//=======================================================================
/** @file PrewittFilter.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines a prewitt edge detection filter in the spatial domain.
 *
 */
//=======================================================================
#ifndef PROJECT_PREWITTFILTER_H
#define PROJECT_PREWITTFILTER_H
/** Class which defines a prewitt edge detection filter in the spatial domain.
 * It is a band pass filter.
 * Example 5 mask: [1 2 0 -2 -1]
 */
#include "StandardFilter.h"
#include <vector>
template <class T>
class PrewittFilter : public StandardFilter<T>{
public:
    /** Standard Constructor
     *  The length is set to 5
     *  We construct an array of length 5 with the middle entry set to 0 and the other ones set
     *  to int(lenght/2) - i where i denotes the distance to the middle entry. One side has minus signs
     *  and one side has positive signs.
     *  Example: 1 2 0 -2 -1
     */
    PrewittFilter();
    /** Constructor with the length of the mask
     *  We construct an array of length 5 with the middle entry set to 0 and the other ones set
     *  to int(lenght/2) - i where i denotes the distance to the middle entry. One side has minus signs
     *  and one side has positive signs.
     * @param pLength int which indicated the length of the filter
     */
    PrewittFilter(int pLength);
};

#include "PrewittFilter_imp.h"

#endif //PROJECT_PREWITTFILTER_H
