//
// Created by shernand on 10/12/17.
//

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
