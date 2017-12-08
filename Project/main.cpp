//
// Created by shernand on 11/30/17.
//

#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

#include "AudioFile.h"
#include "Signal.h"
#include "StandardFilter.h"
#include "MeanFilter.h"
#include "Read.h"

int main(int argc, char* argv[]) {

    /*
    try {
        Signal Sign("../test-audio/wav_mono_16bit_44100.wav");
        std::ofstream write_hist("Histogram.dat");
        Histogram(Sign, 50, write_hist);
        write_hist.close();
    }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
        return 1;
    }*/
    //TODO Testing a filter
    //SDHC: to plot in gnuplot
    //plot "cmake-build-debug/Output_Filter.dat" using 1:2 title "Original", "cmake-build-debug/Output_Filter.dat" using 1:3 title "Filtered"
    ConstructFromFrequency LA_Note(440);
    Signal LA_NoteSignal;
    LA_NoteSignal = LA_Note.construct();

    std::ofstream write_hist("Hist_LA.dat");
    std::ofstream write_fre("Fre_LA.dat");

    LA_NoteSignal.FourierTransformCalculator(-100,500,write_fre);
    LA_NoteSignal.Histogram(50,write_hist);

    std:: ofstream write_sample("Sample_LA.dat");
    LA_NoteSignal.SaveSignal(write_sample);

    LA_NoteSignal.WriteSound("LA440.wav");

    ReadAudioFile Sound("./wav_mono_16bit_44100.wav");
    Signal SoundSignal;
    SoundSignal = Sound.construct();

    std::ofstream write_hist_Sound("Hist_S.dat");
    std::ofstream write_fre_Sound("Fre_S.dat");

    SoundSignal.FourierTransformCalculator(0,500,write_fre_Sound);
    SoundSignal.Histogram(50,write_hist_Sound);

    std:: ofstream write_sample_Sound("Sample_S.dat");
    SoundSignal.SaveSignal(write_sample_Sound);

    SoundSignal.WriteSound("test.wav");

    /*std::ofstream write_tf("inv.dat");

    size_t size_signal(SoundSignal.getTime().size());
    size_t size_fre(SoundSignal.getFrequencies().size());

    std::vector<std::complex<double>> FT = SoundSignal.getFourierTransform();
    std::vector<int> Freq = SoundSignal.getFrequencies();
    double pi(M_PI);

    double sampleRate = 44100.0;

    for (size_t w(0);w<30000;++w){
        std::complex<double> InvFourier(0,0);
        //double t(0.0);
        for (size_t k(0); k < size_fre; ++k) {
            std::complex<double> temp(cos(2 * pi * Freq[k] * w), sin(2 * pi * Freq[k] * w));
            //inv += FT[k].real()*pow(cos((2*pi*t*w)),1)*(1.0/sqrt(size_signal)) - FT[k].imag()*pow(sin((2*pi*t*w)),1)*(1.0/sqrt(size_signal));
            //std::cout<<FT[k] * temp<<std::endl;
            //std::cout<<inv<<std::endl;
            std::complex<double> temp2(FT[k].real()*temp.real()-FT[k].imag()*temp.imag(),FT[k].real()*temp.imag()+FT[k].imag()*temp.real());
            InvFourier += (1.0/sqrt(size_fre))*temp2;
        }
        std::cout<<"w = " << w << std::endl;
        write_tf << w << " " ;
        write_tf << abs(InvFourier) << std::endl;

    }
    write_tf.close();
    */
    /*
    try {



        Signal Sign("../test-audio/wav_mono_16bit_44100.wav");
        int channel = 0;

        std::vector<double> signalToFilter = Sign.getAudioFile().samples[channel];

        std::cout << signalToFilter.size();
        int filterSize = 5;

        StandardFilter<double> meanFilter = StandardFilter<double>(filterSize);
        std::vector<double> maskMean = std::vector<double>(filterSize);

        std::for_each(maskMean.begin(), maskMean.end(),
                      [filterSize](double &x) { x = (1.0/filterSize); }); //Fills the mask
        std::for_each(maskMean.begin(), maskMean.end(),
                      [](double x) { std::cout << x << std::endl; });
        meanFilter.setMask(maskMean);

        std::vector<double> signalFiltered =meanFilter.apply(signalToFilter);

        std::cout << signalFiltered.size();

        MeanFilter<double> myMean = MeanFilter<double>(filterSize);

        std::vector<double> signalFilteredMyMean = myMean.apply(signalToFilter);

        std::cout << signalFilteredMyMean.size();

        std::ofstream write_output("Output_Filter.dat");
        std::vector<double> time;
        int sampleRate = Sign.getAudioFile().getSampleRate();
        int numSamples = Sign.getAudioFile().getNumSamplesPerChannel();
        double step((numSamples /(sampleRate*1.0))/numSamples);

        for (int i = 0; i<numSamples;++i){
            time.push_back(i*step);
        }
        std::cout<<time.size()<<std::endl;
        for (int i = 0; i < numSamples; i++)
        {
            double currentSample = Sign.getAudioFile().samples[channel][i];
            write_output<<time[i]<<" ";
            write_output<<currentSample<<" ";
            write_output<<signalFiltered[i]<<" ";
            write_output<<signalFilteredMyMean[i]<<std::endl;

        }

        write_output.close();
    }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
        return 1;
    }
    */
    return 0;
}