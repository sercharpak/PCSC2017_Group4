//=======================================================================
/** @file main.cpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 * main.cpp is the entry point
 *
 */
//=======================================================================
#include "ConfigFileParser.h"
#include "ConfigFileExecuter.h"
/**
 * Constant to inform the user the correct usage of the program in case of a misuse.
 */
#define USAGE "Please enter correctly one argument (a config file). Example: ./Project configFile.txt"
/**
 * Constant which defines the correct number of arguments the program can receive.
 */
#define N_ARGS 2
/**
 * Main method of the program
 * @param argc int number of arguments received
 * @param argv char* the arguments received.
 * @return int 0 if well executed 1 if not.
 */
int main(int argc, char* argv[]) {
    if(argc!=N_ARGS){
        std::cout<<USAGE<< std::endl;
        return 1;
    }
    try{
        std::string fName = argv[1];
        ConfigFileParser parser = ConfigFileParser();
        parser.parseFile(fName);
        parser.verify();
        ConfigFileExecuter executer = ConfigFileExecuter(parser);
        executer.execute();
        return 0;
    }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
        return 1;
    }
}
