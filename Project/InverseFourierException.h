//=======================================================================
/** @file InverseFourierException.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines an Exception when the user tries to compute the inverse fourier transform of a signal that doesn't
 * have a fourier transform computed yet.
 *
 */
//=======================================================================

#ifndef PROJECT_INVERSEFOURIEREXCEPTION_H
#define PROJECT_INVERSEFOURIEREXCEPTION_H

#include <string>
#include <stdexcept>
class InverseFourierException  : public std::runtime_error{
public:
    InverseFourierException() : std::runtime_error("FOURIER TRANSFORM WAS NOT CALCULATED YET. The fourier transform must be computed before the inverse.") { }
    virtual const char* what() const throw()
    {
        return "FOURIER TRANSFORM WAS NOT CALCULATED YET. The fourier transform must be computed before the inverse.";
    }

};


#endif //PROJECT INVERSEFOURIEREXCEPTION_H
