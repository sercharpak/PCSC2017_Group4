//
// Created by shernand on 11/30/17.
//

#include "AudioFile.h"

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
    audioFile.load ("./tests/AudioFileTests/test-audio/wav_mono_16bit_44100.wav");
    int sampleRate = audioFile.getSampleRate();
    int bitDepth = audioFile.getBitDepth();

    int numSamples = audioFile.getNumSamplesPerChannel();
    double lengthInSeconds = audioFile.getLengthInSeconds();

    int numChannels = audioFile.getNumChannels();
    bool isMono = audioFile.isMono();
    bool isStereo = audioFile.isStereo();

// or, just use this quick shortcut to print a summary to the console
    audioFile.printSummary();
/*
    //Access the samples directly:

    int channel = 0;
    //int numSamples = audioFile.getNumSamplesPerChannel();

    for (int i = 0; i < numSamples; i++)
    {
        double currentSample = audioFile.samples[channel][i];
    }


// Replace the AudioFile audio buffer with another
    // 1. Create an AudioBuffer
// (BTW, AudioBuffer is just a vector of vectors)

    AudioFile<double>::AudioBuffer buffer;

// 2. Set to (e.g.) two channels
    buffer.resize (2);

// 3. Set number of samples per channel
    buffer[0].resize (100000);
    buffer[1].resize (100000);

// 4. do something here to fill the buffer with samples

// 5. Put into the AudioFile object
    bool ok = audioFile.setAudioBuffer (buffer);

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
    audioFile.save ("audioFile.wav");

// Wave file (explicit)
    audioFile.save ("audioFile.wav", AudioFileFormat::Wave);

// Aiff file
    audioFile.save ("audioFile.aif", AudioFileFormat::Aiff);
*/
}