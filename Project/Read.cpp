//
// Created by didier on 04/12/17.
//
//=======================================================================
/** @file Read.cpp
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

ReadAudioFile::ReadAudioFile(std::string n):name(n){}
Signal ReadAudioFile::construct()
{
    AudioFile<double> audio;
    bool load_bool = audio.load(name);
    if (!load_bool)
        throw FileNotFoundException();
    else{
        std::cout<<"File :"<< name << " successfully loaded " << std::endl;
    }
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
        double t = i/sampleRate;//i/numSamples;//i/ 44100.0; // I put everything in the first second of the signal
        sample.push_back(sin(frequency*t*2*pi));
    }

    Signal sign(sample);
    return sign;
}

ReadAmplitudeFile::ReadAmplitudeFile(std::string n) :name(n) {}
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

    FileToRead.close();

    Signal sign(sample);
    return sign;

}

ReadFrequencyFile::ReadFrequencyFile(std::string n, double numS) :name(n),numSamples(numS) {}
Signal ReadFrequencyFile::construct() {
    std::vector<double> sample(numSamples);
    double pi (M_PI);
    double sampleRate(44100.0);

    std::vector<double> frequencies;

    std::ifstream FileToRead(name);

    if (!FileToRead) {//Try if the file can be open
        throw FileNotFoundException();
    }
    else{
        std::cout<<"File :"<< name << " successfully loaded " << std::endl;
    }
    while(true){//Read the values from the file
        double t;
        FileToRead >> t;
        if (FileToRead.eof()){
            break;
        }
        frequencies.push_back(t);
    }

    for (size_t j(0); j < frequencies.size(); ++j){//Create the samples with the given frequencies
        for (int i = 0; i < numSamples; i++)
        {
            double t = i/sampleRate;
            sample[i] += (sin(frequencies[j]*t*2*pi));
        }
    }

    FileToRead.close();


    Signal sign(sample); // Create the signal from the samples we created.
    return sign;
}