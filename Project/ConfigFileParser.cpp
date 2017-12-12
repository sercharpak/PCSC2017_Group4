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
    defaultKeys.push_back("histogram");
    defaultKeys.push_back("type_output");
    defaultKeys.push_back("outputFile");
    defaultFilters.push_back("mean");
    defaultFilters.push_back("prewitt");
    defaultFilters.push_back("laplace");
    defaultIO.push_back("audio");
    defaultIO.push_back("ampl");
    defaultIO.push_back("freq");
}
ConfigFileParser::~ConfigFileParser(){}

void ConfigFileParser::setFilterNames(std::vector<std::string> pFilterNames){
    filterNames = pFilterNames;
}
std::vector<std::string> ConfigFileParser::getFilterNames(){
    return filterNames;
}
std::vector<StandardFilter<double>> ConfigFileParser::getFilters(){
    return filters;
}
std::vector<int> ConfigFileParser::getFilterSizes(){
    return filterSizes;
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
    std::cout<<"Parsing file: " << fName << std::endl;
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

                if(key=="filtersizes"){ //For the filters and filtersizes we have several values for a key
                    std::string token;
                    std::istringstream tokenStream(value);
                    while (std::getline(tokenStream, token,','))
                    {
                        if (!token.empty())
                            filterSizes.push_back(stoi(token));
                        else
                            throw FileParserException();
                    }
                }
                if(key=="filters"){ //For the filters and filtersizes we have several values for a key
                    std::string token;
                    std::istringstream tokenStream(value);
                    while (std::getline(tokenStream, token,','))
                    {
                        if (!token.empty()) {
                            bool correctFilterName = verifyFilterName(token);
                            filterNames.push_back(token);
                        }
                        else
                            throw FileParserException();
                    }
                }

            }
        }
    }
    file.close();
    formFiltersVector();
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

bool ConfigFileParser::verifyFilterName(std::string filterName){
    auto it = defaultFilters.begin();
    auto end = defaultFilters.end();
    auto found = std::find(it,defaultFilters.end(),filterName);
    if(found!=end)
        return true;
    else
        throw FileParserException();
}

void ConfigFileParser::formFiltersVector(){
    if(!filterSizes.empty()){   //If the sizes are specified, there need to be as many sizes than filters
        if(filterSizes.size()!=filterNames.size())
            throw FileParserException();
        else{ //Creates the filters and adds them to the vector
            for(int i=0;i<filterNames.size();++i) {
                std::string filter = filterNames[i];
                int filterSize = filterSizes[i];
                if (filter == "mean") {
                    MeanFilter<double> myMean = MeanFilter<double>(filterSize);
                    filters.push_back(myMean);
                }
                if (filter == "prewitt") {
                    PrewittFilter<double> myEdge = PrewittFilter<double>(filterSize);
                    filters.push_back(myEdge);
                }
                if (filter == "laplace") {
                    LaplaceFilter<double> myLaplace = LaplaceFilter<double>(filterSize);
                    filters.push_back(myLaplace);
                }
                //\todo Can insert here new filter types
            }
        }
    }
    else{   //No sizes are specified
        std::vector<StandardFilter<double>> filters_temp;
        std::for_each(filterNames.begin(), filterNames.end(),
                      [&filters_temp](std::string filter) {
                          if(filter=="mean"){
                              MeanFilter<double> myMean = MeanFilter<double>();
                              filters_temp.push_back(myMean);
                          }
                          if(filter=="prewitt"){
                              PrewittFilter<double> myEdge = PrewittFilter<double>();
                              filters_temp.push_back(myEdge);
                          }
                          if(filter=="laplace"){
                              LaplaceFilter<double> myLaplace = LaplaceFilter<double>();
                              filters_temp.push_back(myLaplace);
                          }
                          //\todo Can insert here new filter types

                      });
        filters = filters_temp;
    }
}