//
// Created by shernand on 10/12/17.
//
//=======================================================================
/** @file FileNotFoundException.hpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class defines an Exception in the case of a file not found required to read.
 *
 */
//=======================================================================
#ifndef FILENOTFOUNDEXCEPTIONDEF
#define FILENOTFOUNDEXCEPTIONDEF

#include <string>
#include <stdexcept>
class FileNotFoundException : public std::runtime_error{
public:
    FileNotFoundException() : std::runtime_error("FILE NOT FOUND: The file cannot be found") { }
    virtual const char* what() const throw()
    {
        return "FILE NOT FOUND: The file cannot be found";
    }

};
#endif //FILENOTFOUNDEXCEPTIONDEF
