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
 * This class defines an Exception in the case of the occurrance of an error during the parsing
 * of the configuration file.
 *
 */
//=======================================================================
#ifndef FILEPARSEREXCEPTIONDEF
#define FILEPARSEREXCEPTIONDEF

#include <string>
#include <stdexcept>
class FileParserException : std::runtime_error{
public:
    FileParserException() : std::runtime_error("FILE PARSER ERROR: The parsing of the file failed. \n Please verify the file is well formatted.") { }
    virtual const char* what() const throw()
    {
        return "FILE PARSER ERROR: The parsing of the file failed. \n Please verify the file is well formatted.";
    }

};
#endif //FILEPARSEREXCEPTIONDEF
