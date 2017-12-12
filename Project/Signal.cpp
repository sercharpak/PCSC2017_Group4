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

Signal::Signal(AudioFile<double> audio):sample(audio.samples[0]),sampleRate(audio.getSampleRate()){
    double numSamples(audio.getNumSamplesPerChannel());
    double step((numSamples /(audio.getSampleRate()*1.0))/numSamples);
    for (int i = 0; i<numSamples;++i){
        time.push_back(i*step);
    }
}

Signal::Signal(std::vector<double> sam, double samRate):sample(sam),sampleRate(samRate){
    double numSamples(sam.size());
    //double SampleRate(44100); // Provisoire to have a signal with a sample rate of the length of the signal
    double step((numSamples /(sampleRate*1.0))/numSamples);
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

double Signal::getSampleRate() const{
    return sampleRate;
}


void Signal::Histogram(int number_bin, std::string fileName){
    std::ofstream file(fileName);
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
    double w(min_frequency);
    while (w<max_frequency){
        std::complex<double> Fourier_transform(0,0);
        //std::cout << w << std::endl;
        //We use a sampling rate of 44100...
        for (size_t k(0); k < size; ++k) {
            //double t((k*1.0)/size);// I can use this if the sample rate is = numSample
            double t(k/sampleRate);// I can use this if the sample rate is 44100.0
            //int t(k/size);
            //std::complex<double> temp(sample[k] * cos((2*M_PI*t*w))*(1.0/(sqrt(size))),(-1.0) * sample[k] * sin((2*M_PI*t*w))*(1.0/(sqrt(size))));
            std::complex<double> temp(sample[k] * cos((2*M_PI*t*w)),(-1.0) * sample[k] * sin((2*M_PI*t*w)));
            Fourier_transform += (1.0/sqrt(size))*temp;
        }
        FourierTransform.push_back(Fourier_transform);
        Frequencies.push_back(w);
        w+=1;
        //std::cout<< w << std::endl;
    }
    std::cout<<"Fourier Transform calculated successfully" << std::endl;
}

void Signal::FourierTransformCalculator(int min_frequency, int max_frequency, std::string fileName) {
    std::ofstream file(fileName);
    Signal::FourierTransformCalculator(min_frequency,max_frequency);
    for (size_t i (0); i<Frequencies.size(); ++i){// Store the Fourier Transform into a file.
        file << Frequencies[i] << " ";
        file << std::abs(FourierTransform[i]) << std::endl;
    }
    file.close();
}

void Signal::SaveSignal(std::string fileName){
    std::ofstream file(fileName);
    for (size_t i(0); i< sample.size(); ++i){ // Save the signal and the samples into a file.
        file << time[i] << " ";//Change this to not have the time in the file
        file << sample[i] << std::endl;
    }

    std::cout<<"Signal saved successfully" << std::endl;
    file.close();
}

std::vector<double> Signal::InverseFourierTransform(std::string fileName){
    std::ofstream file(fileName);
    size_t sizeFre(Frequencies.size());
    size_t sizeSam(sample.size());
    std::vector<std::complex<double>> ResultSample;
    std::vector<std::complex<double>> Fourier = FourierTransform;
    std::vector<int> Freque = Frequencies;

    std::vector<double> EndSample(sizeSam);
    for (int w(0);w<sizeSam;++w){
        std::complex<double> InvFourier_transform(0,0);
        for (size_t k(0); k < sizeFre; ++k) {
            double t((k*1.0)/sampleRate);
            std::complex<double> temp(cos((2*M_PI*t*w)),sin((2*M_PI*t*w)));
            InvFourier_transform += (1.0/sizeFre)*Fourier[k] *temp;
        }
        ResultSample.push_back(InvFourier_transform);
        EndSample[w] = ResultSample[w].real();
        file << w << " ";
        file << InvFourier_transform.real() <<std::endl;
    }

    std::cout<<"Inverse Fourier Transform calculated sucessfully" << std::endl;
    file.close();
    return EndSample;

}

void Signal::WriteSound(std::string fileName){

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
    audioFile.setSampleRate(44100);

    //  Save the audio file to disk

    // Wav file (implicit)

    audioFile.save(fileName);

    std::cout<<"Audio file : " << fileName << " saved " << std::endl;
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


