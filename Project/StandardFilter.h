//
// Created by Sergio Daniel Hernandez on 12/3/17.
//

#ifndef PCSC2017_GROUP4_STANDARDFILTER_H
#define PCSC2017_GROUP4_STANDARDFILTER_H
/*
 * Class which defines the standard  of a filter on our signal.
 */
#include <math.h>
#include <vector>
template <class T>
class StandardFilter {
protected:
    /** Numerator coefficients of the mask of the filter.
     */
    std::vector<T> mask;
    /** Length of the mask of the filter
    */
    int length;
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
    /** Applies the filter to the signal
     * @param Signal the signal to which we want to apply the filter.
     * @return the Signal filtered
     */
    //TODO change the std::vector<T> with the Signal class
    std::vector<T> apply(std::vector<T> pSignal);

};

#include "StandardFilter_imp.h"


#endif //PCSC2017_GROUP4_STANDARDFILTER_H
