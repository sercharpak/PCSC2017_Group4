//
// Created by laptop on 12/15/17.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <complex>

#include "Signal.h"
#include "Read.h"
#include "FrequencyFilter.h"
#include "HighPassFrequencyFilter.h"
#include "LowPassFrequencyFilter.h"
#include "BandPassFrequencyFilter.h"

int main(int argc, char* argv[]) {
    try {
        //Construct the signal from the frequency for DO, RE, MI
        std::string freq_tests ="freq_Filters_Test.dat";
        std::ofstream file(freq_tests);
        double freq_1=50.0;
        double freq_2=200.0;
        double freq_3=500.0;
        std::vector<double> freqs;
        freqs.push_back(freq_1);
        freqs.push_back(freq_2);
        freqs.push_back(freq_3);
        for(int i = 0;i<freqs.size();++i){
            file << freqs[i] << std::endl;
        }
        ReadFrequencyFile  reader(freq_tests,3000);
        Signal song;
        song = reader.construct();

        song.WriteSound("Song_Test.wav");


        //Computes the Fourier transform of the signal
        song.FourierTransformCalculator();
        std::string songFreq ="Song_Test_Fourier.dat";
        song.WriteFourier(songFreq);

        //------Single Frequency Filter
        FrequencyFilter mySingle = FrequencyFilter(freq_1);
        Signal do_OutputSignal = mySingle.apply(song);
        //Inverse Transform it
        std::vector<double> do_OutputSamples(do_OutputSignal.InverseFourierTransform());
        do_OutputSignal.setSamples(do_OutputSamples);
        std::string songSingleFreq ="Song_Single_Fourier.dat";
        do_OutputSignal.WriteFourier(songSingleFreq);
        songSingleFreq ="Song_Single.wav";
        do_OutputSignal.WriteSound(songSingleFreq);

        //------High Pass Filter
        HighPassFrequencyFilter myHighPass = HighPassFrequencyFilter(freq_2+10.0);
        Signal re_mi_OutputSignal = myHighPass.apply(song);
        //Inverse Transform it
        std::vector<double> re_mi_OutputSamples(re_mi_OutputSignal.InverseFourierTransform());
        do_OutputSignal.setSamples(re_mi_OutputSamples);
        std::string songHighPass ="Song_HighPass_Fourier.dat";
        do_OutputSignal.WriteFourier(songHighPass);
        songHighPass ="Song_HighPass.wav";
        do_OutputSignal.WriteSound(songHighPass);
        //------Low Pass Filter
        LowPassFrequencyFilter myLowPass = LowPassFrequencyFilter(freq_2+10.0);
        Signal low_OutputSignal = myLowPass.apply(song);
        //Inverse Transform it
        std::vector<double> low_OutputSamples(low_OutputSignal.InverseFourierTransform());
        low_OutputSignal.setSamples(low_OutputSamples);
        std::string songLowPass ="Song_LowPass_Fourier.dat";
        low_OutputSignal.WriteFourier(songLowPass);
        songLowPass ="Song_LowPass.wav";
        low_OutputSignal.WriteSound(songLowPass);
        //------Band Pass Filter
        std::vector<double> bandPassVec;
        bandPassVec.push_back(freq_1+10);
        bandPassVec.push_back(freq_3-10);
        BandPassFrequencyFilter myBandPass = BandPassFrequencyFilter(bandPassVec);
        Signal band_OutputSignal = myBandPass.apply(song);
        //Inverse Transform it
        std::vector<double> band_OutputSamples(band_OutputSignal.InverseFourierTransform());
        band_OutputSignal.setSamples(band_OutputSamples);
        std::string songBandPass ="Song_BandPass_Fourier.dat";
        band_OutputSignal.WriteFourier(songBandPass);
        songBandPass ="Song_BandPass.wav";
        band_OutputSignal.WriteSound(songBandPass);

    }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
        return 1;
    }


    return 0;
}