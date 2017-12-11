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
    defaultKeys.push_back("type_input");
    defaultKeys.push_back("filename");
    defaultKeys.push_back("fourierWrite");
    defaultKeys.push_back("type_output");
    defaultKeys.push_back("outputFile");
}
ConfigFileParser::~ConfigFileParser(){}

void ConfigFileParser::setFilters(std::vector<std::string> pFilters){
    filters = pFilters;
}
std::vector<std::string> ConfigFileParser::getFilters(){
    return filters;
}
std::vector<int> ConfigFileParser::getFilterSizes(){
    return filtersizes;
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
        if (temp.empty()) //Empty Line
            continue;
        if(temp.front() =='#') //Comment Line
            continue;

        std::istringstream str_line(temp);
        std::string key;
        if( std::getline(str_line, key, '=') )
        {
            std::string value;
            if( std::getline(str_line, value) ){
                if (!key.empty() && !value.empty()) //Verify that the two values exist
                    data[key] = value;
                else
                    throw FileParserException();

                if(key=="filters"){ //For the filters and filtersizes we have several values for a key
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
                if(key=="filtersizes"){ //For the filters and filtersizes we have several values for a key
                    std::string token;
                    std::istringstream tokenStream(value);
                    while (std::getline(tokenStream, token,','))
                    {
                        if (!token.empty())
                            filtersizes.push_back(stoi(token));
                        else
                            throw FileParserException();
                    }
                }
                if(!filtersizes.empty()) //If the sizes are specified, there need to be as many sizes than filters
                    if(filtersizes.size()!=filters.size())
                        throw FileParserException();
            }
        }
    }
    file.close();
}
void ConfigFileParser::verify(){
    //std::for_each(defaultKeys.begin(), defaultKeys.end(),
     //             [](std::string defaultKey) {
     //                 valueExistsForKey(defaultKey);
     //             });
    for(int i=0;i<defaultKeys.size();++i){
        std::string defaultKey = defaultKeys[i];
        valueExistsForKey(defaultKey);
    }

}
bool ConfigFileParser::valueExistsForKey(std::string key){
    auto iter = data.find(key);
    if (iter == data.end())
        throw FileParserException();
    else
        return true;
}