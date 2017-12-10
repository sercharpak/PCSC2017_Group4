//=======================================================================
/** @file Signal.cpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 * This class is useful to handle a signal.
 */
//=======================================================================

#include "Signal.h"

Signal::Signal(AudioFile<double> audio):sample(audio.samples[0]){
    double numSamples(audio.getNumSamplesPerChannel());
    double step((numSamples /(audio.getSampleRate()*1.0))/numSamples);
    for (int i = 0; i<numSamples;++i){
        time.push_back(i*step);
    }
}

Signal::Signal(std::vector<double> sam):sample(sam){
    double numSamples(sam.size());
    double SampleRate(44100);
    double step((numSamples /(SampleRate*1.0))/numSamples);
    for (int i = 0; i<numSamples;++i){
        time.push_back(i*step);
    }
}

Signal::~Signal(){}

std::vector<double> Signal::getTime() const{
    return time;
}

std::vector<double> Signal::getSamples() const{
    return sample;
}

std::vector<std::complex<double>> Signal::getFourierTransform() const{
    return FourierTransform;
}

std::vector<int> Signal::getFrequencies() const{
    return Frequencies;
}

void Signal::Histogram(int number_bin, std::ofstream& file){

    std::vector<double> audio = sample; // Do a copy of the vector of samples.
    int channel = 0; // Choose the channel (in c++ notation, starting from 0).
    int numSamples = sample.size(); // Calculating the size of the vector of samples.

    std::sort(audio.begin(),audio.end());// Sort the array of sample.

    double pas((audio[numSamples-1]-audio[0])/number_bin);

    double bin(audio[0] + pas);
    double value_per_bin(0);

    for (int i = 0; i < numSamples; i++)
    {

        double currentSample = audio[i];

        if (currentSample> bin){ // Either we change the bin (if we are bigger than the current bin).
            file << bin << " ";
            file << value_per_bin << std::endl;
            bin += pas;
            value_per_bin = 0;
        }
        value_per_bin +=1;// Or we increase the number of values in the current bin.

    }
}

void Signal::FourierTransformCalculator(int min_frequency, int max_frequency){
    if (min_frequency > max_frequency){//Check if the values are not in the wrong order...
        int temp (min_frequency);
        min_frequency = max_frequency;
        max_frequency = temp;
        //std::swap(min_frequency,max_frequency); Doesnt work
    }

    size_t size(sample.size());

    for (int w(min_frequency);w<=max_frequency;++w){
        std::complex<double> Fourier_transform(0,0);
        //We use a sampling rate of 44100...
        for (size_t k(0); k < size; ++k) {
            double t(k/44100.0);
            std::complex<double> temp(sample[k] * cos((2*M_PI*t*w))*(1.0/(sqrt(size))),(-1.0) * sample[k] * sin((2*M_PI*t*w))*(1.0/(sqrt(size))));
            Fourier_transform += temp;
        }
        FourierTransform.push_back(Fourier_transform);
        Frequencies.push_back(w);
    }
    std::cout<<"Fourier Transform calculated successfully" << std::endl;
}

void Signal::FourierTransformCalculator(int min_frequency, int max_frequency, std::ofstream& file) {
    Signal::FourierTransformCalculator(min_frequency,max_frequency);
    for (size_t i (0); i<Frequencies.size(); ++i){// Store the Fourier Transform into a file.
        file << Frequencies[i] << " ";
        file << std::abs(FourierTransform[i]) << std::endl;
    }
}

void Signal::SaveSignal(std::ofstream& file){
    for (size_t i(0); i< sample.size(); ++i){ // Save the signal and the samples into a file.
        file << time[i] << " ";
        file << sample[i] << std::endl;
    }

    std::cout<<"Signal saved successfully" << std::endl;
}

void Signal::InverseFourierTransform(){
    //Compute the inverse Fourier Transform
}

void Signal::WriteSound(std::string FileName){

    AudioFile<double> audioFile;// Define an object of the class AudioFile.
    double numSamples = sample.size();
    AudioFile<double>::AudioBuffer buffer;
    buffer.resize(1);
    buffer[0].resize(numSamples);

    for (int i = 0; i < numSamples; i++)// File the buffer with the signal
    {
        buffer[0][i] = sample[i];
    }

    bool ok = audioFile.setAudioBuffer(buffer);//Faire un try-catch...

    // Set the number of samples per channel
    audioFile.setNumSamplesPerChannel (numSamples);

    // Set the number of channels
    audioFile.setNumChannels (1);

    // Set bit depth and sample rate
    audioFile.setBitDepth (16);
    audioFile.setSampleRate (44100);

    //  Save the audio file to disk

    // Wav file (implicit)

    audioFile.save(FileName);



    std::cout<<"Audio file : " << FileName << " saved " << std::endl;
}

Signal concatenate(const Signal& S1,const Signal& S2) {
    std::vector<double> Sf = S1.getSamples();// Copy the first vector.
    double sizeS2(S2.getSamples().size());
    for (size_t i(0); i < sizeS2; ++i){ // Add the second vector behind the first one.
        Sf.push_back(S2.getSamples()[i]);
    }

    Signal sign(Sf);
    std::cout << "Concatenation done" << std::endl;

    return Sf;
}


