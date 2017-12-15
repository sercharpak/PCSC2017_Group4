//
// Created by shernand on 10/12/17.
//
//=======================================================================
/** @file FileParserException.hpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines an Exception in the case of the occurrence of an error during the execution of
 * a Fourier Filter.
 *
 */
//=======================================================================
#ifndef FOURIER_FILTER_DEF
#define FOURIER_FILTER_DEF

#include <string>
#include <stdexcept>
class FourierFilterException : public std::runtime_error{
public:
    FourierFilterException() : std::runtime_error("FOURIER FILTER EXCEPTION: Cut frequencies not assigned correctly \n Add one frequency for a only one frequency pass, or low or high pass and two frequencies for a band pass.") { }
    virtual const char* what() const throw()
    {
        return "FOURIER FILTER EXCEPTION: Cut frequencies not assigned correctly \n Add one frequency for a only one frequency pass, or low or high pass and two frequencies for a band pass.";   }

};
#endif //FOURIER_FILTER_DEF
