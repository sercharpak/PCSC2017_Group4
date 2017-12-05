//
// Created by didier on 02/12/17.
//

#ifndef PROJECT_SIGNAL_H
#define PROJECT_SIGNAL_H

#include "AudioFile.h"
#include <stdexcept>
#include <fstream>
#include <algorithm>


class Signal{
private:
    std::vector<double> time;
    std::vector<double> FourierTransform; //Need to put complex number
    std::vector<double> sample;
    //AudioFile<double> audioFile;
public:
    /** Constructors */
    //Signal(std::string name);
    Signal(AudioFile<double> audio);
    Signal(std::vector<double> sam);
    Signal();

    /** Destructor */
    ~Signal();


    /** Getters */
    std::vector<double> getTime() const;

    /** Histogramm */
    void Histogram(int number_bin,std::ofstream& file) ;

};



#endif //PROJECT_SIGNAL_H
