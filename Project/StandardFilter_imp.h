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
template<typename T> StandardFilter<T>::StandardFilter()
{
    length=5;
    mask = std::vector<T>(length);
}

template<typename T> StandardFilter<T>::StandardFilter(int pLength)
{
    //Checks if the length is even
    if(pLength % 2 == 0){
        throw FilterSizeException();
    }
    length=pLength;
    mask = std::vector<T>(pLength);
}
template<typename T> StandardFilter<T>::StandardFilter(std::vector<T> pMask)
{
    mask=pMask;
}

template<typename T>
StandardFilter<T>::~StandardFilter(){}

template<typename T>
void StandardFilter<T>::setMask(std::vector<T> pMask)
{
    mask=pMask;
}
template<typename T>
std::vector<T> StandardFilter<T>::getMask()
{
    return mask;
}

template<typename T>
void StandardFilter<T>::setLength(int pLength)
{
    length=pLength;
}
template<typename T>
int StandardFilter<T>::getLength()
{
    return length;
}

template<typename T>
std::vector<T> StandardFilter<T>::apply(std::vector<T> pSignal)
{
    //\todo Verify that the mirror boundary conditions are correct
    //\todo Use some of the new C++ features here (for_each, iota, etc...)
    //\todo verify if no recursion can be done as a standard manner.
    int n = pSignal.size();
    std::vector<T> outputSignal = std::vector<T>(n);
    int l0 = (length -1)/2;
    std::cout << l0;
    for (int i = 0; i < n; ++i) {
        T outputValue = 0;
        for (int j = -l0; j <= l0; ++j) {
            int index = j+i;
            if(index < 0){
                index = - index;
            }
            if(index > (n-1)){
                index = 2*(n-1) - index;
            }
            outputValue = outputValue + mask[j]*pSignal[index];
        }
        outputSignal[i] = outputValue;
    }
    return outputSignal;
}
template<typename T>
Signal StandardFilter<T>::apply(Signal pSignal)
{
    std::vector<T> samples = pSignal.getSamples();
    std::vector<T> outSamples = apply(samples);
    Signal outputSignal = Signal(outSamples);
    return outputSignal;
}