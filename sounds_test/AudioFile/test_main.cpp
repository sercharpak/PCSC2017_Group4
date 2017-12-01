//
// Created by shernand on 11/30/17.
//

#include "AudioFile.h"
#include <fstream>
#include <vector>
#include <cmath>

int main(int argc, char* argv[]) {
    //Examples taken from: https://github.com/adamstark/AudioFile
    /*
    A Note On Types

    AudioFile is a template class and so it can be instantiated using floating point precision:

    AudioFile<float> audioFile;

    ...or double precision:

    AudioFile<double> audioFile;
    */

    AudioFile<double> audioFile;
    audioFile.load ("./wav_mono_16bit_44100.wav");
    int sampleRate = audioFile.getSampleRate();
    int bitDepth = audioFile.getBitDepth();

    int numSamples = audioFile.getNumSamplesPerChannel();
    double lengthInSeconds = audioFile.getLengthInSeconds();

    int numChannels = audioFile.getNumChannels();
    bool isMono = audioFile.isMono();
    bool isStereo = audioFile.isStereo();

// or, just use this quick shortcut to print a summary to the console
    audioFile.printSummary();

    //Access the samples directly:

    int channel = 0;
    //int numSamples = audioFile.getNumSamplesPerChannel();

    double sinStep (2*M_PI/numSamples);

    std::ofstream write_output("Output.dat");
    std::vector<double> time;
    double step((numSamples /(sampleRate*1.0))/numSamples);

    for (int i = 0; i<numSamples;++i){
        time.push_back(i*step);
    }
    std::cout<<time.size()<<std::endl;
    for (int i = 0; i < numSamples; i++)
    {
        audioFile.samples[channel][i] = (16.0/15.0)*cos(50*i*step)-(1.0/15.0)*cos(5.0*i*step)+cos(3.0*i*step)-(13.0/15.0)*cos(40*i*step)-(1.0/13.0)*cos(6.0*i*step)+cos(9.0*i*step)-(16.0/14.0)*cos(0.3*i*step)-(3.0/11.0)*cos(5.0*i*step)+cos(5.0*i*step)-(11.0/33.0)*cos(5*i*step)-(1.0/13.0)*cos(6.0*i*step)+cos(9.0*i*step);
        double currentSample = audioFile.samples[channel][i];
        write_output<<time[i]<<" ";
        write_output<<currentSample<<std::endl;

    }

    write_output.close();


// Replace the AudioFile audio buffer with another
    // 1. Create an AudioBuffer
// (BTW, AudioBuffer is just a vector of vectors)

    AudioFile<double>::AudioBuffer buffer;

// 2. Set to (e.g.) one channels
    buffer.resize (1);

// 3. Set number of samples per channel
    buffer[0].resize (numSamples);
    //buffer[1].resize (100000);


// 4. do something here to fill the buffer with samples
    for (int i = 0; i < numSamples; i++)
    {
        if(i%1 == 0) {
            buffer[0][i] = (16.0/15.0)*cos(50*i*step)-(1.0/15.0)*cos(5.0*i*step)+cos(3.0*i*step)-(13.0/15.0)*cos(40*i*step)-(1.0/13.0)*cos(6.0*i*step)+cos(9.0*i*step)-(16.0/14.0)*cos(0.3*i*step)-(3.0/11.0)*cos(5.0*i*step)+cos(5.0*i*step)-(11.0/33.0)*cos(5*i*step)-(1.0/13.0)*cos(6.0*i*step)+cos(9.0*i*step);
        }
        else{
            buffer[0][i] = audioFile.samples[channel][i];
        }
    }
// 5. Put into the AudioFile object
    bool ok = audioFile.setAudioBuffer(buffer);

    // Resize the audio buffer

    // Set both the number of channels and number of samples per channel
    audioFile.setAudioBufferSize (numChannels, numSamples);

// Set the number of samples per channel
    audioFile.setNumSamplesPerChannel (numSamples);

// Set the number of channels
    audioFile.setNumChannels (numChannels);

    // Set bit depth and sample rate
    audioFile.setBitDepth (24);
    audioFile.setSampleRate (44100);

    //  Save the audio file to disk

    // Wave file (implicit)
    //audioFile.save ("audioFile.wav");

//Wave file (explicit)
    audioFile.save ("audioFile.wav", AudioFileFormat::Wave);

/*
// Aiff file
    audioFile.save ("audioFile.aif", AudioFileFormat::Aiff);
*/
}