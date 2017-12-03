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
    AudioFile<double> audioFile;
public:
    /** Constructors */
    Signal(std::string name);

    /** Destructor */
    ~Signal();


    /** Getters */
    std::vector<double> getTime() const;
    AudioFile<double> getAudioFile() const;



};

/** Histogramm */ // Je l'ai mis à l'extérieur mais peut-être mieux dans la classe
void Histogram(const Signal& Sign, int number_bin,std::ofstream& file);

#endif //PROJECT_SIGNAL_H
