//
// Created by shernand on 12/8/17.
//

#ifndef PROJECT_LAPLACEFILTER_H
#define PROJECT_LAPLACEFILTER_H
/** Class which defines a laplace filter in the spatial domain.
 * It is a high pass filter.
 * Example 5 mask: [1 1 -4 1 1]
 */
#include "StandardFilter.h"
#include <vector>
template <class T>
class LaplaceFilter : public StandardFilter<T>{
public:
    /** Standard Constructor
     *  The length is set to 5
     *  We construct an array of length 5 with the middle entry set to -(lenght-1) and the other ones set
     *  to 1
     *  Example: [1 1 -4 1 1]
     */
    LaplaceFilter();
    /** Constructor with the length of the mask
     *  We construct an array of given length with the middle entry set to -(lenght-1) and the other ones set
     *  to 1
     * @param pLength int which indicated the length of the filter
     */
    LaplaceFilter(int pLength);
};

#include "LaplaceFilter_imp.h"

#endif //PROJECT_LAPLACEFILTER_H
