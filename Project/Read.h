//
// Created by didier on 04/12/17.
//

#ifndef PROJECT_READ_H
#define PROJECT_READ_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Signal.h"


class ConstructSignal {
public:
    /** Method Construct */
    virtual Signal construct () = 0;

};
//IMPORTANT: THE FILE NAMES MUST BE IN ABSOLUTE
class ReadAudioFile:public ConstructSignal{
private:
    std::string name;
public:
    ReadAudioFile(std::string n);
    virtual Signal construct() override;
};

class ConstructFromFrequency: public ConstructSignal{
private:
    double frequency;
public:
    ConstructFromFrequency(double f);
    virtual Signal construct() override ;
};

class ReadAmplitudeFile : public ConstructSignal{
private:
    std::string name;
public:
    ReadAmplitudeFile(std::string n);
    virtual Signal construct() override ;
};


#endif //PROJECT_READ_H
