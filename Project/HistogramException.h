//=======================================================================
/** @file HistogramException.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines an Exception in the case of a wrong number of bins in the histogram in the class Signal.
 *
 */
//=======================================================================

#ifndef PROJECT_HISTOGRAMEXCEPTION_H
#define PROJECT_HISTOGRAMEXCEPTION_H

#include <string>
#include <stdexcept>
class HistogramException  : public std::runtime_error{
public:
    HistogramException() : std::runtime_error("HISTOGRAM SIZE IS SMALLER OR EQUAL TO 0. It must be stricly bigger than 0") { }
    virtual const char* what() const throw()
    {
        return "HISTOGRAM SIZE IS SMALLER OR EQUAL TO 0. It must be stricly bigger than 0";
    }

};


#endif //PROJECT_HISTOGRAMEXCEPTION_H
