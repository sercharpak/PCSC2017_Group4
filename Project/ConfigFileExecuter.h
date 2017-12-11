//
// Created by shernand on 12/11/17.
//
//=======================================================================
/** @file ConfigFileExecuter.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This class performs executes the program from the previously parsed config file
 *
 */
//=======================================================================
#ifndef PROJECT_CONFIGFILEEXECUTER_H
#define PROJECT_CONFIGFILEEXECUTER_H

#include "ConfigFileParser.h"
#include "Signal.h"
#include "MeanFilter.h"
#include "PrewittFilter.h"
#include "LaplaceFilter.h"
#include "Read.h"

/** Class to execute from a parsed configuration file following the standard specified in the documentation.
 */
class ConfigFileExecuter {
public:
    /** Standard Constructor
     * @param ConfigFileParser configFile the previously parsed and verified config file
     */
    ConfigFileExecuter(ConfigFileParser pConfigFile);
    /** Standard Destructor
     */
    ~ConfigFileExecuter();
    /**
     * Excutes the given parsed configuration
     */
    void execute();

private:
    /**
     * The previously parsed and verified config file from which the program executes
     */
    ConfigFileParser configFile;
};


#endif //PROJECT_CONFIGFILEEXECUTER_H
