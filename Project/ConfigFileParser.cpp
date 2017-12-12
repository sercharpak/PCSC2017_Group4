//
// Created by shernand on 12/10/17.
//
//=======================================================================
/** @file ConfigFileParser.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class performs the parsing of a standard configuration file.
 *
 */
//=======================================================================
#include "ConfigFileParser.h"

ConfigFileParser::ConfigFileParser() {
}
ConfigFileParser::~ConfigFileParser(){}

void ConfigFileParser::setFilters(std::vector<std::string> pFilters){
    filters = pFilters;
}
std::vector<std::string> ConfigFileParser::getFilters(){
    return filters;
}
std::map<std::string,std::string> ConfigFileParser::getData(){
    return data;
}

void ConfigFileParser::setData(std::map<std::string,std::string> pData)
{
    data=pData;
}
std::string ConfigFileParser::getFName(){
    return fName;
}

void ConfigFileParser::parseFile(std::string pFname){
    fName = pFname;
    std::ifstream file;
    file.open(fName.c_str());
    if (!file)
        throw FileNotFoundException();
    std::string line;
    while (std::getline(file, line))
    {
        std::string temp = line;
        if (temp.empty())
            continue;
        if(temp.front() =='#') //Comment Line
            continue;

        std::istringstream is_line(temp);
        std::string key;
        if( std::getline(is_line, key, '=') )
        {
            std::string value;
            if( std::getline(is_line, value) ){
                if (!key.empty() && !value.empty())
                    data[key] = value;
                else
                    throw FileParserException();

                if(key=="filters"){
                    std::string token;
                    std::istringstream tokenStream(value);
                    while (std::getline(tokenStream, token,','))
                    {
                        if (!token.empty())
                            filters.push_back(token);
                        else
                            throw FileParserException();
                    }
                }
            }
        }
    }
    file.close();
}