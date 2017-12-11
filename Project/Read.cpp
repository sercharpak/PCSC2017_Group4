//
// Created by didier on 04/12/17.
//
//=======================================================================
/** @file Read.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This classes are useful to generate a signal from different ways
 *
 */
//=======================================================================

#include "Read.h"

ReadAudioFile::ReadAudioFile(std::string n):name(n){
    std::cout<<"File :"<< n << " successfully loaded " << std::endl;
}
Signal ReadAudioFile::construct()
{
    AudioFile<double> audio;
    bool load_bool = audio.load(name);
    if (!load_bool)
        throw FileNotFoundException();
    Signal sign (audio);
    return sign;
}

ConstructFromFrequency::ConstructFromFrequency(double f, double n):frequency(f), numSamples(n){}
Signal ConstructFromFrequency::construct()
{
    std::vector<double> sample;
    double pi (M_PI);
    double sampleRate(44100.0);


    for (int i = 0; i < numSamples; i++)
    {
        double t = i/ 44100.0;
        sample.push_back(sin(frequency*t*2*pi));
    }

    Signal sign(sample);
    return sign;
}

ReadAmplitudeFile::ReadAmplitudeFile(std::string n) :name(n){
    std::cout<<"File :"<< n << " successfully loaded " << std::endl;
}
Signal ReadAmplitudeFile::construct()
{
    std::vector<double> sample;
    std::ifstream FileToRead(name);
    if (!FileToRead)
        throw FileNotFoundException();
    while(!FileToRead.eof()){
        double t,s;
        FileToRead >> t >> s;
        sample.push_back(s);
    }

    Signal sign(sample);
    return sign;

}