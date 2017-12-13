//
// Created by shernand on 12/4/17.
//
//=======================================================================
/** @file MeanFilter_imp.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines a mean filter in the spatial domain.
 *
 */
//=======================================================================
#include "MedianFilter.h"
MedianFilter::MedianFilter()
{
    length=5;
    name="Median Filter (impulse noise removal)";
    mask = std::vector<double>(length);
    std::for_each(mask.begin(), mask.end(),
                  [](double &x) { x = (1.0); }); //Fills the mask
}
MedianFilter::MedianFilter(int pLength)
{
    length=pLength;
    name="Median Filter (impulse noise removal)";
    mask = std::vector<double>(length);
    std::for_each(mask.begin(), mask.end(),
                  [](double &x) { x = (1.0); }); //Fills the mask
}

int MedianFilter::getLength()
{
    return length;
}

std::string MedianFilter::getName()
{
    return name;
}

std::vector<double> MedianFilter::applySamples(std::vector<double> pSignal){
    int n = pSignal.size();
    std::vector<double> outputSignal = std::vector<double>(n);
    int l0 = (length -1)/2;
    std::vector<double> temp = std::vector<double>(length);
    for (int i = 0; i < n; ++i) {
        double outputValue = 0;
        for (int j = -l0; j <= l0; ++j) {
            int index = j+i;
            if(index < 0){
                index = - index;
            }
            if(index > (n-1)){
                index = 2*(n-1) - index;
            }
            temp[j+l0] = mask[j+l0]*pSignal[index];
        }
        std::sort(temp.begin(), temp.end());
        outputValue = temp[l0];
        outputSignal[i] = outputValue;
    }
    return outputSignal;
}

Signal MedianFilter::apply(Signal pSignal)
{
    std::vector<double> samples = pSignal.getSamples();
    std::vector<double> outSamples = applySamples(samples);
    Signal outputSignal = Signal(outSamples);
    return outputSignal;
}