//
// Created by shernand on 12/4/17.
//

#ifndef PROJECT_MEANFILTER_H
#define PROJECT_MEANFILTER_H


#include "StandardFilter.h"
#include <vector>
template <class T>
class MeanFilter : public StandardFilter<T>{
public:
    /** Standard Constructor
     *  The length is set to 5
     *  We construct an array of given length with all the entries set as 1/length
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
