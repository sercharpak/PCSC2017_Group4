//
// Created by laptop on 12/3/17.
//

#include "StandardFilter.h"
template <class T>
StandardFilter<T>::StandardFilter(int pLenght)
{
    mask = std::vector<T>(pLenght);
}
template <class T>
StandardFilter<T>::StandardFilter(std::vector<T> pMask)
{
    mask=pMask;
}

template <class T>
StandardFilter<T>::~StandardFilter(){}

template <class T>
void StandardFilter<T>::setMask(std::vector<T> pMask)
{
    mask=pMask;
}
template <class T>
std::vector<T> StandardFilter<T>::getMask()
{
    return mask;
}

template <class T>
void StandardFilter<T>::setLength(int pLength)
{
    length=pLength;
}
template <class T>
int StandardFilter<T>::getLength()
{
    return length;
}

template <class T>
std::vector<T> StandardFilter<T>::apply(std::vector<T> pSignal)
{
    //TODO Manage properly the boundary conditions.
    //TODO Use some of the new C++ features here (for_each, iota, etc...)
    //TODO verify if no recursion can be done as a standard manner.
    std::vector<T> outputSignal = std::vector<T>(pSignal.size());
    for (int i = 0; i < pSignal.size(); ++i) {
        //TODO Signal class should have a get neighborhood method
        // std::vector<T> get_neigborhood(x, lenght)
        std::vector<T> neighborhood = std::vector<T>(length);
        T outputValue = 0;
        for (int j = 0; j < length; ++j) {
            outputValue = outputValue + mask[j]*neighborhood[j];
        }
        outputSignal[i] = outputValue;
    }
    return outputSignal;
}