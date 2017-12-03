//
// Created by Sergio Daniel Hernandez on 12/3/17.
//

#ifndef PCSC2017_GROUP4_ABSTRACTFILTER_H
#define PCSC2017_GROUP4_ABSTRACTFILTER_H
/*
 * Class which defines the standard  of a filter on our signal.
 */
#include <math.h>
#include <vector>
template <class T>
class AbstractFilter {
public:
    /*
     * Constructor
     */
    AbstractFilter();
    /*
     * Constructor with the mask
     */
    AbstractFilter(std::vector<T> pMask);
    //virtual ~AbstractFilter();
    /*
     * Sets a 1D mask given by parameter
     * @param std::vector<T> the mask to be set
     */
    void setMask(std::vector<T> pMask);
    /*
     * Gives the 1D mask of the filter
     * @return std::vector<T> the mask of the filter
     */
    std::vector<T> getMask(std::vector<T> pMask);
    /*
     * Applies the filter to the signal
     * @param Signal the signal to which we want to apply the filter.
     * @return the Signal filtered
     */
    //TODO change the std::vector<T> with the Signal class
    std::vector<T> apply(std::vector<T> pSignal);

private:
    /*
     * Numerator coefficients of the rational transfer function, specified as a vector.
     */
    std::vector<T> mask;
};


#endif //PCSC2017_GROUP4_ABSTRACTFILTER_H
