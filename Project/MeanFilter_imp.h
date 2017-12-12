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
template<typename T> MeanFilter<T>::MeanFilter() : StandardFilter<T>()
{
    this->setLength(5);
    this->setName("Mean Filter (low pass)");
    int pLength = this->length;
    std::vector<T> pMask =this->mask;
    pMask = std::vector<T>(pLength);
    std::for_each(pMask.begin(), pMask.end(),
                  [pLength](T &x) { x = (1.0/pLength); }); //Fills the mask
    this->setMask(pMask);
}
template<typename T> MeanFilter<T>::MeanFilter(int pLength) : StandardFilter<T>(pLength)
{
    this->setLength(pLength);
    this->setName("Mean Filter (low pass)");
    std::vector<T> mask = std::vector<T>(pLength);
    std::for_each(mask.begin(), mask.end(),
                  [pLength](T &x) { x = (1.0/pLength); }); //Fills the mask
    this->setMask(mask);
}