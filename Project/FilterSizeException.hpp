//
// Created by shernand on 10/12/17.
//
//=======================================================================
/** @file FilterSizeException.hpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines an Exception in the case of a wrong filter size delivered to a StandardFilter class object.
 *
 */
//=======================================================================
#ifndef FILTERSIZEEXCEPTIONDEF
#define FILTERSIZEEXCEPTIONDEF

#include <string>
#include <stdexcept>
class FilterSizeException : std::runtime_error{
public:
    FilterSizeException() : std::runtime_error("FILTER SIZE ERROR: Filter size must be odd (3,5,7, etc...)") { }
    virtual const char* what() const throw()
    {
        return "FILTER SIZE ERROR: Filter size must be odd (3,5,7, etc...)";
    }
};
#endif //FILTERSIZEEXCEPTIONDEF
