//
// Created by shernand on 11/30/17.
//

/*
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>


#include "AudioFile.h"
#include "Signal.h"
#include "StandardFilter.h"
#include "MeanFilter.h"
#include "PrewittFilter.h"
#include "LaplaceFilter.h"
#include "Read.h"
#include "FilterSizeException.hpp"

#include "FileNotFoundException.hpp"
#include "FileParserException.hpp"
#include "ConfigFileParser.h"

int testFiltersSpatial();
int testFiltersSpatialSignal();
int testIDFT();
int testConfigParser();
int testConfigParserClass();


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
    /*
    ConstructFromFrequency LA_Note(3);
    Signal LA_NoteSignal;
    LA_NoteSignal = LA_Note.construct();

    LA_NoteSignal.FourierTransformCalculator(0,500,"Fre_LA.dat");
    LA_NoteSignal.Histogram(50,"Hist_LA.dat");

    LA_NoteSignal.SaveSignal("Sample_LA.dat");

    LA_NoteSignal.WriteSound("LA440.wav");

    ReadAudioFile Sound("../test-audio/wav_mono_16bit_44100.wav");
    Signal SoundSignal;
    SoundSignal = Sound.construct();

    SoundSignal.FourierTransformCalculator(0,500,"Fre_S.dat");
    SoundSignal.Histogram(50,"Hist_S.dat");

    SoundSignal.SaveSignal("Sample_S.dat");



    std::ofstream write_tf("inv.dat");
    std::vector<double> InvFourier;
    InvFourier = LA_NoteSignal.InverseFourierTransform(write_tf);
    /*
    size_t size(LA_NoteSignal.getFrequencies().size());
    std::cout<<"Size : "<<size<<std::endl;
    std::vector<std::complex<double>> ResultSample;
    std::vector<std::complex<double>> Fourier = LA_NoteSignal.getFourierTransform();
    std::vector<int> Freque = LA_NoteSignal.getFrequencies();

    std::vector<double> EndSample(352800);
    int pause(0);
    //Voir si je peux encore améliorer ou si je suis déjà au max de ce que je peux faire
    //IMPORTANT : Je dois faire que tout le code marche donc j'ai modifié des choses dans la classe ReadFre
    // et aussi dans la classe signal et aussi dans les constructeurs et les attributs donc il faut faire en sorte que ça nmarche encore
    for (int w(0);w<352800;++w){
        std::complex<double> Fourier_transform(0,0);
        //We use a sampling rate of 44100...
        for (size_t k(0); k < size; ++k) {
            //double t(k/44100.0);
            double t((k*1.0)/44100.0);
            std::complex<double> temp(cos((2*M_PI*t*w)),sin((2*M_PI*t*w)));
            Fourier_transform += (1.0/sqrt(size))*Fourier[k] *temp;
            /*
            std::cout<<"======================="<<std::endl;
            std::cout<<"Frequence : "<< Freque[k] << std::endl;
            std::cout<<"temp : "<< temp << std::endl;
            std::cout<<"Fourier: " << Fourier[k] <<std::endl;
            std::cout<<"Fourier Transform :"<< Fourier_transform << std::endl;
            std::cout<<"Time : " << t << std::endl;
            std::cout << "(2*M_PI*t*w) : " << (2*M_PI*t*w) << std::endl;
            std::cout<<"======================="<<std::endl;
            */
            //if (pause == 5){
            //    std::cin >> pause;
            //}
            //++pause;
    /*
        }
        ResultSample.push_back(Fourier_transform);
        EndSample[w] = ResultSample[w].real()+ ResultSample[w].imag();
        write_tf << w << " ";
        write_tf << (ResultSample[w].real()) << std::endl;
        std::cout<<w << std::endl;
    }

    Signal SignFI(EndSample);

    SignFI.WriteSound("Retour.wav");
   */
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
    //int testSpatialFilters = testFiltersSpatial();
    //int testSpatialFilterSignals = testFiltersSpatialSignal();
    //SDHC \todo Testing my own DFT and IDFT so far it DOES NOT WORK
    //int testIDFTs = testIDFT();

    return 0;
}
/*


    //SHDC \todo Testing the config file parser
    //int testConfigParsers = testConfigParser();
    int testConfigParserClasss = testConfigParserClass();




    return 0;
}
int testConfigParser(){
    try{
        std::string fName = "../input_options.txt";
        std::cout<<"Testing Parser with file = " << fName << std::endl;
        std::ifstream file;
        file.open(fName.c_str());
        if (!file)
            throw FileNotFoundException();

        std::string line;
        std::vector<std::string> filters;
        std::map<std::string,std::string> data;

        while (std::getline(file, line))
        {
            std::string temp = line;
            //std::cout<<"Line = " << temp << std::endl;
            if (temp.empty())
                continue;
            if(temp.front() =='#'){
                std::cout<<"Comment line = " << temp << std::endl;
                continue;
            }
            std::istringstream is_line(temp);
            std::string key;
            if( std::getline(is_line, key, '=') )
            {
                std::string value;
                if( std::getline(is_line, value) ){
                    std::cout<<"Key = " << key << std::endl;
                    std::cout<<"Value = " << value << std::endl;
                    data[key] = value;
                    if(key=="filters"){

                        std::string token;
                        std::istringstream tokenStream(value);
                        while (std::getline(tokenStream, token,','))
                        {
                            filters.push_back(token);
                        }
                    }
                }
            }
        }
        file.close();
        //Finished parsing the config file

        std::for_each(filters.begin(), filters.end(),
                      [](std::string x) { std::cout << x << std::endl; });

        auto it = data.begin();
        auto end = data.end();
        for (; it != end; ++it) {
            std::string key = it->first;
            std::string value = it->second;
            std::cout << "key:" << key << " -> ";
            std::cout << value << std::endl;
        }
        return 0;


    }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
*/
//=======================================================================
/** @file main.cpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 * main.cpp is the entry point
 *
 */
//=======================================================================
#include "ConfigFileParser.h"
#include "ConfigFileExecuter.h"
#include <cmath>

/**
 * Constant to inform the user the correct usage of the program in case of a misuse.
 */
#define USAGE "Please enter correctly one argument (a config file). Example: ./Project configFile.txt"
/**
 * Constant which defines the correct number of arguments the program can receive.
 */
#define N_ARGS 2
/**
 * Main method of the program
 * @param argc int number of arguments received
 * @param argv char* the arguments received.
 * @return int 0 if well executed 1 if not.
 */
int main(int argc, char* argv[]) {
    if(argc!=N_ARGS){
        std::cout<<USAGE<< std::endl;
        return 1;
    }
    try{
        std::string fName = argv[1];
        ConfigFileParser parser = ConfigFileParser();
        parser.parseFile(fName);
        parser.verify();
        ConfigFileExecuter executer = ConfigFileExecuter(parser);
        executer.execute();

        //Trying some Stuff
        //=======================================================

        ConstructFromFrequency LA_Note(440);
        Signal LA_NoteSignal;
        LA_NoteSignal = LA_Note.construct();

        LA_NoteSignal.FourierTransformCalculator(0,500,"Fre_LA.dat");
        LA_NoteSignal.Histogram(-3,"Hist_LA.dat"); //Does not give the message of error...

        LA_NoteSignal.SaveSignal("Sample_LA.dat");

        LA_NoteSignal.WriteSound("LA440.wav");

        std::vector<double> InvFourier;
        InvFourier = LA_NoteSignal.InverseFourierTransform("Inv.dat"); // Not the good Height...

        //=======================================================

        return 0;

    }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
        return 1;
    }

}


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
/*
int testFiltersSpatial(){
    try {


        ReadAudioFile Sound("../test-audio/wav_mono_16bit_44100.wav");
        Signal SoundSignal;
        SoundSignal = Sound.construct();

        std::vector<double> signalToFilter = SoundSignal.getSamples();
        int numSamples = signalToFilter.size();
        std::cout << "Size of the input signal " << signalToFilter.size()<< std::endl;

        int filterSize = 5;

        MeanFilter<double> myMean = MeanFilter<double>(filterSize);
        std::vector<double> signalFilteredMyMean = myMean.apply(signalToFilter);
        std::cout << "Size of the mean signal " << signalFilteredMyMean.size()<< std::endl;

        PrewittFilter<double> myEdge = PrewittFilter<double>(filterSize);
        std::vector<double> signalFilteredMyEdge = myEdge.apply(signalToFilter);
        std::cout << "Size of the Prewitt edge signal " << signalFilteredMyEdge.size()<< std::endl;


}

*/
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
}