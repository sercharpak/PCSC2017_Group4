//
// Created by shernand on 12/8/17.
//
//=======================================================================
/** @file LaplaceFilter.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines a laplace filter in the spatial domain.
 *
 */
//=======================================================================
template<typename T> LaplaceFilter<T>::LaplaceFilter() : StandardFilter<T>()
{
    this->setLength(5);
    this->setName("Laplace Filter (high pass)");
    int pLength = this->length;
    std::vector<T> pMask =this->mask;
    pMask = std::vector<T>(pLength);
    //\todo Find a way to implement the Laplace with iota or foreach
    //Fills the mask
    int half = pLength/2;
    for(int i = 0; i<=half;i++){
        pMask[i] = 1;
        pMask[pLength-1-i] = 1;
    }
    pMask[half]=-(pLength-1);
    this->setMask(pMask);
}
template<typename T> LaplaceFilter<T>::LaplaceFilter(int pLength) : StandardFilter<T>(pLength)
{
    this->setLength(pLength);
    this->setName("Laplace Filter (high pass)");
    std::vector<T> mask = std::vector<T>(pLength);
    int half = pLength/2;
    for(int i = 0; i<=half;i++){
        mask[i] = 1;
        mask[pLength-1-i] = 1;
    }
    mask[half]=-(pLength-1);
    this->setMask(mask);
}