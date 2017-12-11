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
#include "PrewittFilter.h"
#include "LaplaceFilter.h"
#include "Read.h"
#include "FilterSizeException.hpp"
/*
int testFiltersSpatial();
int testFiltersSpatialSignal();
int testIDFT();
*/
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

    ConstructFromFrequency LA_Note(3);
    Signal LA_NoteSignal;
    LA_NoteSignal = LA_Note.construct();

    std::ofstream write_hist("Hist_LA.dat");
    std::ofstream write_fre("Fre_LA.dat");

    LA_NoteSignal.FourierTransformCalculator(-100,500,write_fre);
    LA_NoteSignal.Histogram(50,write_hist);

    std:: ofstream write_sample("Sample_LA.dat");
    LA_NoteSignal.SaveSignal(write_sample);

    LA_NoteSignal.WriteSound("LA440.wav");

    ReadAudioFile Sound("../test-audio/wav_mono_16bit_44100.wav");
    Signal SoundSignal;
    SoundSignal = Sound.construct();

    std::ofstream write_hist_Sound("Hist_S.dat");
    std::ofstream write_fre_Sound("Fre_S.dat");

    SoundSignal.FourierTransformCalculator(0,500,write_fre_Sound);
    SoundSignal.Histogram(50,write_hist_Sound);

    std:: ofstream write_sample_Sound("Sample_S.dat");
    SoundSignal.SaveSignal(write_sample_Sound);

    std::ofstream write_tf("inv.dat");

    size_t size(SoundSignal.getFrequencies().size());
    std::vector<std::complex<double>> ResultSample;
    std::vector<std::complex<double>> Fourier = SoundSignal.getFourierTransform();
    std::vector<int> Freque = SoundSignal.getFrequencies();

    std::vector<double> EndSample(352800);

    for (int w(0);w<=352800;++w){
        std::complex<double> Fourier_transform(0,0);
        //We use a sampling rate of 44100...
        for (size_t k(0); k < size; ++k) {
            //double t(k/44100.0);
            double t(Freque[k]/44100.0);
            std::complex<double> temp(cos((2*M_PI*t*w)),sin((2*M_PI*t*w)));
            Fourier_transform += (1.0/size)*Fourier[k] *temp;
        }
        ResultSample.push_back(Fourier_transform);
        EndSample[w] = ResultSample[w].real()+ ResultSample[w].imag();
        write_tf << w << " ";
        write_tf << (ResultSample[w].real()) << std::endl;
        std::cout<<w << std::endl;
    }

    Signal SignFI(EndSample);

    SignFI.WriteSound("Retour.wav");
    /**/

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


    //SDHC \todo Testing the Spatial Domain Filters
    int testSpatialFilters = testFiltersSpatial();
    int testSpatialFilterSignals = testFiltersSpatialSignal();
    //SDHC \todo Testing my own DFT and IDFT so far it DOES NOT WORK
    //int testIDFTs = testIDFT();
     */
    return 0;
}
/*
int testIDFT(){
    try{
        Signal SoundSignal;
        //ReadAudioFile Sound("../test-audio/wav_mono_16bit_44100.wav");
        ConstructFromFrequency LA_Note(440);
        SoundSignal = LA_Note.construct();

        //SoundSignal = Sound.construct();

        //Testing DFT
        std::vector<double> signalOrig = SoundSignal.getSamples();
        int N = signalOrig.size();

        std::vector<std::complex<double>> signalDFT = std::vector<std::complex<double>>(N);
        std::vector<double> frequencies = std::vector<double>(N);

        //For all frequencies it takes too long
        //We need to put some limits for the possible frequencies

        std::cout << "Computing the DTF " << std::endl;

        for (int k=0;k<N;++k){
            //Value k
            std::complex<double> sum(0,0);
            for (int n=0;n<N;++n){
                //Sum
                double x_n = signalOrig[n];
                double exp_arg = (-2.0*M_PI*k*n)/N ;
                std::complex<double> sum_temp(x_n*cos(exp_arg),x_n*sin(exp_arg));
                sum = sum + sum_temp;
            }
            signalDFT[k]=sum;
            double freq = k/N;
            frequencies[k]=freq;
        }
        std::cout << "Finished computing the DTF " << std::endl;

        std::cout << "Computing the IDTF " << std::endl;
        std::vector<double> signalRecov = std::vector<double>(N);
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
                sum = sum + sum_temp;
            }
            signalRecov[n]=sum.real();
        }

        std::cout << "Finished computing the IDTF " << std::endl;

        std::vector<double> time = SoundSignal.getTime();

        std::ofstream write_output("Output_DFT.dat");
        for (int i = 0; i < N; i++)
        {
            write_output<<time[i]<<" ";
            write_output<<signalOrig[i]<<" ";
            write_output<<frequencies[i]<<" ";
            write_output<<signalDFT[i].real()<<std::endl;
            write_output<<signalRecov[i]<<std::endl;

        }

        write_output.close();
        return 0;
    }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
        return 1;
    }
}

int testFiltersSpatial(){
    try {


        ReadAudioFile Sound("../test-audio/wav_mono_16bit_44100.wav");
        Signal SoundSignal;
        SoundSignal = Sound.construct();

        std::vector<double> signalToFilter = SoundSignal.getSamples();
        int numSamples = signalToFilter.size();
        std::cout << "Size of the input signal " << signalToFilter.size()<< std::endl;

        int filterSize = 6;

        MeanFilter<double> myMean = MeanFilter<double>(filterSize);
        std::vector<double> signalFilteredMyMean = myMean.apply(signalToFilter);
        std::cout << "Size of the mean signal " << signalFilteredMyMean.size()<< std::endl;

        PrewittFilter<double> myEdge = PrewittFilter<double>(filterSize);
        std::vector<double> signalFilteredMyEdge = myEdge.apply(signalToFilter);
        std::cout << "Size of the Prewitt edge signal " << signalFilteredMyEdge.size()<< std::endl;

        LaplaceFilter<double> myLaplace = LaplaceFilter<double>(filterSize);
        std::vector<double> signalFilteredMyLaplace = myLaplace.apply(signalToFilter);
        std::cout << "Size of the Lapalcian signal " << signalFilteredMyLaplace.size()<< std::endl;


        std::ofstream write_output("Output_Filter.dat");
        std::vector<double> time = SoundSignal.getTime();
        std::cout << "Size of the time " << time.size()<< std::endl;
        for (int i = 0; i < numSamples; i++)
        {
            write_output<<time[i]<<" ";
            write_output<<signalToFilter[i]<<" ";
            write_output<<signalFilteredMyMean[i]<<" ";
            write_output<<signalFilteredMyEdge[i]<<" ";
            write_output<<signalFilteredMyLaplace[i]<<std::endl;

        }

        write_output.close();
        return 0;
    }
        catch (FilterSizeException &e){
            std::cout << e.what() <<std::endl;
            return 1;
        }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
        return 1;
    }
}

int testFiltersSpatialSignal(){
    try {
        ReadAudioFile Sound("../test-audio/wav_mono_16bit_44100.wav");
        Signal SoundSignal;
        SoundSignal = Sound.construct();

        std::vector<double> signalToFilter = SoundSignal.getSamples();
        int numSamples = signalToFilter.size();
        std::cout << "Size of the input signal " << signalToFilter.size()<< std::endl;

        int filterSize = 5;

        MeanFilter<double> myMean = MeanFilter<double>(filterSize);
        Signal signalFilteredMyMean = myMean.apply(SoundSignal);
        std::cout << "Size of the mean signal " << signalFilteredMyMean.getSamples().size()<< std::endl;

        PrewittFilter<double> myEdge = PrewittFilter<double>(filterSize);
        Signal signalFilteredMyEdge = myEdge.apply(SoundSignal);
        std::cout << "Size of the Prewitt edge signal " << signalFilteredMyEdge.getSamples().size()<< std::endl;

        LaplaceFilter<double> myLaplace = LaplaceFilter<double>(filterSize);
        Signal signalFilteredMyLaplace = myLaplace.apply(SoundSignal);
        std::cout << "Size of the Laplace signal " << signalFilteredMyLaplace.getSamples().size()<< std::endl;


        std::ofstream write_output("Output_Filter_Signal.dat");
        std::vector<double> time = SoundSignal.getTime();
        std::cout << "Size of the time " << time.size()<< std::endl;

        std::vector<double> meanSamples = signalFilteredMyMean.getSamples();
        std::vector<double> edgeSamples = signalFilteredMyEdge.getSamples();
        std::vector<double> laplaceSamples = signalFilteredMyLaplace.getSamples();
        for (int i = 0; i < numSamples; i++)
        {
            write_output<<time[i]<<" ";
            write_output<<signalToFilter[i]<<" ";
            write_output<<meanSamples[i]<<" ";
            write_output<<edgeSamples[i]<<" ";
            write_output<<laplaceSamples[i]<<std::endl;

        }

        write_output.close();


        return 0;
    }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
        return 1;
    }
}*/