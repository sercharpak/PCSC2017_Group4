//
// Created by didier on 02/12/17.
//

#include "Signal.h"


Signal::Signal(std::string name){
    //Need to add the loading of the data and check if it is open...
    //Two cases : 1) We check for the parameters
                //2) We do a constructor from a string

    //AudioFile<double> audio;
    //audioFile = audio ;

    if(audioFile.load(name)==false){//Voir si c'est la meilleure manière de faire
        throw std::runtime_error("ERROR: The file you want doesn't exist...");
    };

    double numSamples(audioFile.getNumSamplesPerChannel());
    double step((numSamples /(audioFile.getSampleRate()*1.0))/numSamples);

    for (int i = 0; i<numSamples;++i){
        time.push_back(i*step);
    }

    //In the constructor, need to have the fourier transform of the signal.
}

Signal::~Signal(){}

std::vector<double> Signal::getTime() const{
    return time;
}

AudioFile<double> Signal::getAudioFile() const{
    return audioFile;
}

void Histogram(const Signal& Sign, int number_bin, std::ofstream& file){

    AudioFile<double> audio = Sign.getAudioFile();

    int channel = 0;
    int numSamples = audio.getNumSamplesPerChannel();

    std::sort(audio.samples[channel].begin(),audio.samples[channel].end());

    double pas((audio.samples[channel][numSamples-1]-audio.samples[channel][0])/number_bin);

    double bin(audio.samples[channel][0] + pas);
    double value_per_bin(0);

    file << bin << " ";
    file << 0 << std::endl;


    for (int i = 0; i < numSamples; i++)
    {

        double currentSample = audio.samples[channel][i];

        if (currentSample> bin){
            double dessin(pas/20); // Parameter useful to plot the histogramm in gnuplot
            for (size_t j(0); j<20; j++) {
                file << bin + dessin*j << " ";
                file << value_per_bin << std::endl;
            }
            file <<bin+pas << " ";
            file<<0<<std::endl;
            bin += pas;
            value_per_bin = 0;
        }
        value_per_bin +=1;

    }

}
