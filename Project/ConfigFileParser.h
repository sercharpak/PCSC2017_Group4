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
#ifndef PROJECT_CONFIGFILEPARSER_H
#define PROJECT_CONFIGFILEPARSER_H

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "FileNotFoundException.hpp"
#include "FileParserException.hpp"

/** Class to parse a configuration file following the standard specified in the documentation.
 */
class ConfigFileParser {
private:
    /**
     * The filename (path) of the configuration file
     */
    std::string fName;
    /**
     * The map of the keys and values specified in the configuration file
     * The filters are parsed later on and specified in a vector
     */
    std::map<std::string,std::string> data;

    /**
     * The vector of the different filters to apply to the signal
     */
    std::vector<std::string> filters;

public:
    /** Standard Constructor
     */
    ConfigFileParser();
    /** Standard Destructor
     */
    ~ConfigFileParser();
    /**
     * Sets the name of the filters (in order) to be executed
     * @param std::vector<std::string> pFilters the filters to be executed
     */
    void setFilters(std::vector<std::string> pFilters);
    /**
     * Gets the name of the filters (in order) to be executed
     * @return std::vector<std::string> filters the filters to be executed
     */
    std::vector<std::string> getFilters();
    /** Gives the map of the keys and values in the configuration file
     * @return std::map<std::string,std::string> The map of the configuration file
     */
    std::map<std::string,std::string> getData();
    /** Sets the map of the keys and values in the configuration file
     * @param std::map<std::string,std::string> pData The map of the configuration file
     */
    void setData(std::map<std::string,std::string> pData);
    /** Gives the name (path) of the configfile
     * @return std::string the name (path) of the configfile
     */
    std::string getFName();

    /**
     * Parses the file and stores the resulting map and filters vector
     * @param pFname The filename (path) of the configuration file
     */
    void parseFile(std::string pFname);


};


#endif //PROJECT_CONFIGFILEPARSER_H
