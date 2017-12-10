//
// Created by shernand on 11/13/17.
//

#ifndef EXCEPTIONDEF
#define EXCEPTIONDEF

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
#endif //EXCEPTIONDEF
