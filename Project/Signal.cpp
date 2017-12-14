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

std::vector<double> Signal::getFrequencies() const{
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

    file << "# File containing the Histogram of the signal computed with the method 'Histogram' in the project sound processing"
         << std::endl;
    file << "# BIN, NUMBER OF VALUES" << std::endl;

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

void Signal::FourierTransformCalculator(){
    std::vector<double> signalOrig = sample;
    size_t N = signalOrig.size();

    std::vector<std::complex<double>> signalDFT = std::vector<std::complex<double>>(N);
    std::vector<double> Frequencies = std::vector<double>(N);

    std::cout << "Computing the DTF " << std::endl;

    for (size_t k=0;k<N;++k){
        //Value k
        std::complex<double> sum(0,0);
        for (size_t n=0;n<N;++n){
            //Sum
            double x_n = signalOrig[n];
            double exp_arg = (2.0*M_PI*k*n)/N ;
            std::complex<double> sum_temp(x_n*cos(exp_arg),(-1.0)*x_n*sin(exp_arg));
            sum = (sum + sum_temp);
        }
        signalDFT[k]=sum;
        double freq = k * samplerate / N;
        Frequencies[k] = freq;
    }

    frequencies = Frequencies;
    fouriertransform = signalDFT;

    std::cout << "Finished computing the DTF " << std::endl;
}

void Signal::WriteFourier(std::string fileName){
    std::ofstream file(fileName);
    if(fouriertransform.empty()) {//Avoid recomputing the fourier transform (heavy computationnaly)
        Signal::FourierTransformCalculator();
    }

    file << "# File containing the modulus of the fourier transform of the signal computed with the method 'WriteFourier' in the project sound processing"
         << std::endl;
    file << "# FREQUENCIES, AMPLITUDES" << std::endl;

    for (size_t i (0); i<frequencies.size(); ++i){// Store the Fourier Transform into a file.
        file << frequencies[i] << " ";
        file << std::abs(fouriertransform[i]) << std::endl;
    }
    file.close();
}

void Signal::SaveSignal(std::string fileName){
    std::ofstream file(fileName);

    file << "# File containing the amplitude of the signal computed with the method 'SaveSignal' in the project sound processing"
         << std::endl;
    file << "# TIME, SAMPLES" << std::endl;

    for (size_t i(0); i< sample.size(); ++i){ // Save the signal and the samples into a file.
        file << time[i] << " ";//Change this to not have the time in the file
        file << sample[i] << std::endl;
    }

    std::cout<<"Signal saved successfully" << std::endl;
    file.close();
}

std::vector<double> Signal::InverseFourierTransform(){
    if(fouriertransform.empty()){
        throw InverseFourierException();
    }
    std::vector<double> signalOrig = getFrequencies();
    size_t N = signalOrig.size();

    std::cout << "Computing the IDTF " << std::endl;

    std::vector<double> signalRecov = std::vector<double>(N);
    std::vector<std::complex<double>> signalDFT = fouriertransform;

    for (int n=0;n<N;++n){
        //Value k
        std::complex<double> sum(0,0);
        for (int k=0;k<N;++k){
            //Sum
            std::complex<double> X_k = signalDFT[k];
            double exp_arg = (2.0*M_PI*k*n)/N ;
            double real_part = X_k.real()*cos(exp_arg) - X_k.imag()*sin(exp_arg);
            double imag_part = X_k.real()*sin(exp_arg) + X_k.imag()*cos(exp_arg);
            std::complex<double> sum_temp(real_part,imag_part);
            sum += sum_temp;
        }
        signalRecov[n]=(1.0/N)*sum.real();
    }

    std::cout << "Finished computing the IDTF " << std::endl;

    return signalRecov;


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

    return Sf;
}


