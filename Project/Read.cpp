//
// Created by didier on 04/12/17.
//

#include "Read.h"

ReadAudioFile::ReadAudioFile(std::string n):name(n){}
Signal ReadAudioFile::construct()
{
    AudioFile<double> audio;
    audio.load(name);
    audio.printSummary();
    Signal sign (audio);
    return sign;
}

ConstructFromFrequency::ConstructFromFrequency(double f):frequency(f){}
Signal ConstructFromFrequency::construct()
{
    double numSamples (352800.0);
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

ReadAmplitudeFile::ReadAmplitudeFile(std::string n) :name(n){}
Signal ReadAmplitudeFile::construct()
{
    //Lire le fichier et créer le signal
}