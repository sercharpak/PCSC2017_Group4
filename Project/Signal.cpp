//
// Created by didier on 02/12/17.
//

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

Signal::Signal(){}

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

    std::vector<double> audio = sample;
    int channel = 0;
    int numSamples = sample.size();

    std::sort(audio.begin(),audio.end());

    double pas((audio[numSamples-1]-audio[0])/number_bin);

    double bin(audio[0] + pas);
    double value_per_bin(0);

    for (int i = 0; i < numSamples; i++)
    {

        double currentSample = audio[i];

        if (currentSample> bin){
            file << bin << " ";
            file << value_per_bin << std::endl;
            bin += pas;
            value_per_bin = 0;
        }
        value_per_bin +=1;

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
    for (size_t i (0); i<Frequencies.size(); ++i){
        file << Frequencies[i] << " ";
        file << std::abs(FourierTransform[i]) << std::endl;
    }

    std::cout<<"Fourier Transform calculated successfully" << std::endl;
}

void Signal::SaveSignal(std::ofstream& file){
    for (size_t i(0); i< sample.size(); ++i){
        file << time[i] << " ";
        file << sample[i] << std::endl;
    }

    std::cout<<"Signal saved successfully" << std::endl;
}

void Signal::InverseFourierTransform(){
    //Compute the inverse Fourier Transform
}

void Signal::WriteSound(std::string FileName){

    AudioFile<double> audioFile;
    double numSamples = sample.size();
    AudioFile<double>::AudioBuffer buffer;
    buffer.resize(1);
    buffer[0].resize(numSamples);
    double pi (M_PI);

    //double w1 (44100.0 / 400.0);

    for (int i = 0; i < numSamples; i++)
    {
        //double t = i/ 44100.0;
        buffer[0][i] = sample[i];//sin(440*i);

    }

    bool ok = audioFile.setAudioBuffer(buffer);

    // Set the number of samples per channel
    audioFile.setNumSamplesPerChannel (numSamples);

// Set the number of channels
    audioFile.setNumChannels (1);

    // Set bit depth and sample rate
    audioFile.setBitDepth (16);
    audioFile.setSampleRate (44100);

    //  Save the audio file to disk

    // Wave file (implicit)
    audioFile.save (FileName);
}


