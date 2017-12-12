//=======================================================================
/** @file Signal.cpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 * Signal is the core class of the program. It contains the raw sound signals and the
 * Fourier Transform related methods. It can also computes the histogram of the signal
 * and perform the i/o task for a sound file..
 */
//=======================================================================

#include "Signal.h"

Signal::Signal(AudioFile<double> audio):sample(audio.samples[0]),samplerate(audio.getSampleRate()){
    double numSamples(audio.getNumSamplesPerChannel());
    double step((numSamples /(audio.getSampleRate()*1.0))/numSamples);
    for (int i = 0; i<numSamples;++i){
        time.push_back(i*step);
    }
}

Signal::Signal(std::vector<double> sam, double samRate):sample(sam),samplerate(samRate){
    double numSamples(sam.size());
    double step((numSamples /(samplerate*1.0))/numSamples);
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
    return fouriertransform;
}

std::vector<int> Signal::getFrequencies() const{
    return frequencies;
}

double Signal::getSampleRate() const{
    return samplerate;
}


void Signal::Histogram(int number_bin, std::string fileName){
    if (number_bin<= 0){ //Check if the number of bin is positive.
        throw HistogramException();
    }

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

    std::cout << "Histogram calculated sucessfully" << std::endl;
}

void Signal::FourierTransformCalculator(int min_frequency, int max_frequency){
    if (min_frequency > max_frequency){//Check if the values are not in the wrong order...
        int temp (min_frequency);
        min_frequency = max_frequency;
        max_frequency = temp;
    }

    size_t size(sample.size());
    for (int w(min_frequency); w<max_frequency; w++){
        std::complex<double> Fourier_transform(0,0);
        for (size_t k(0); k < size; ++k) {
            double t(k/samplerate);
            std::complex<double> temp(sample[k] * cos((2*M_PI*t*w)),(-1.0) * sample[k] * sin((2*M_PI*t*w)));
            Fourier_transform += (1.0/sqrt(size))*temp;
        }
        fouriertransform.push_back(Fourier_transform);
        frequencies.push_back(w);
    }
    std::cout<<"Fourier Transform calculated successfully" << std::endl;
}

void Signal::FourierTransformCalculator(int min_frequency, int max_frequency, std::string fileName) {
    std::ofstream file(fileName);
    Signal::FourierTransformCalculator(min_frequency,max_frequency);
    for (size_t i (0); i<frequencies.size(); ++i){// Store the Fourier Transform into a file.
        file << frequencies[i] << " ";
        file << std::abs(fouriertransform[i]) << std::endl;
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
    size_t sizeFre(frequencies.size());
    size_t sizeSam(sample.size());
    std::vector<std::complex<double>> ResultSample;
    std::vector<std::complex<double>> Fourier = fouriertransform;
    std::vector<int> Freque = frequencies;

    std::vector<double> EndSample(sizeSam);
    for (int w(0);w<sizeSam;++w){
        std::complex<double> InvFourier_transform(0,0);
        for (size_t k(0); k < sizeFre; ++k) {
            double t((k*1.0)/samplerate);
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


