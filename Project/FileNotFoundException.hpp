//
// Created by shernand on 10/12/17.
//

#ifndef FILENOTFOUNDEXCEPTIONDEF
#define FILENOTFOUNDEXCEPTIONDEF

#include <string>
#include <stdexcept>
class FileNotFoundException : std::runtime_error{
public:
    FileNotFoundException() : std::runtime_error("FILE NOT FOUND: The file cannot be found") { }
    virtual const char* what() const throw()
    {
        return "FILE NOT FOUND: The file cannot be found";
    }

};
#endif //FILENOTFOUNDEXCEPTIONDEF
