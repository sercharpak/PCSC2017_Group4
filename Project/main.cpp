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
#include "HistogramException.h"


int testIDFT();

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
        /*
        std::string fName = argv[1];
        ConfigFileParser parser = ConfigFileParser();
        parser.parseFile(fName);
        parser.verify();
        ConfigFileExecuter executer = ConfigFileExecuter(parser);
        executer.execute();
        */
        //Trying some Stuff
        //=======================================================


        ConstructFromFrequency LA_Note(300,10000);

        //ConstructFromFrequency LA_Note(440);
        Signal LA_NoteSignal;
        LA_NoteSignal = LA_Note.construct();
        /*
        LA_NoteSignal.FourierTransformCalculator(0,500,"Fre_LA.dat");
        LA_NoteSignal.Histogram(50,"Hist_LA.dat"); //Does not give the message of error...

        LA_NoteSignal.SaveSignal("Sample_LA.dat");

        LA_NoteSignal.WriteSound("LA440.wav");

        std::vector<double> InvFourier;
        InvFourier = LA_NoteSignal.InverseFourierTransform("Inv.dat"); // Not the good Height...

        std::cout << "PI = " << M_PI << std::endl;

        int a(testIDFT());*/

        LA_NoteSignal.FourierTransformCalculator();
        std::ofstream fft ("fft.dat");
        for (size_t i(0); i < LA_NoteSignal.getFrequencies().size(); ++i){
            fft << LA_NoteSignal.getFrequencies()[i] << " ";
            fft << std::abs(LA_NoteSignal.getFourierTransform()[i]) << std::endl;
        }

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
        ConstructFromFrequency LA_Note(4000,10000);
        SoundSignal = LA_Note.construct();

        //SoundSignal2 = Sound.construct();


        //Testing DFT
        std::vector<double> signalOrig = SoundSignal.getSamples();


        size_t N = signalOrig.size();
        //size_t N = signalOrig.size()/16;
        /*
        std::vector<double>NewSample(N);

        for (size_t i(0); i<N; ++i){
            NewSample[i] = signalOrig[i];
        }
*/
        //Signal SoundSignal(NewSample);


        std::cout<<"Value in 0 = "<<signalOrig[0] << std::endl;

        std::vector<std::complex<double>> signalDFT = std::vector<std::complex<double>>(N);
        std::vector<double> frequencies = std::vector<double>(N/2.0);

        //For all frequencies it takes too long
        //We need to put some limits for the possible frequencies

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
            if(k<=N/2.0) {
                double freq = k * 44100.0 / N;
                frequencies[k] = freq;
            }
        }
        std::vector<std::complex<double>> FT_S(frequencies.size());
        for (size_t i(0); i<frequencies.size(); ++i){
            FT_S[i] = signalDFT[i];
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
                sum += sum_temp;
            }
            signalRecov[n]=(1.0/N)*sum.real();
        }

        std::cout << "Finished computing the IDTF " << std::endl;

        std::vector<double> time = SoundSignal.getTime();

        std::ofstream write_output("Output_DFT.dat");
        std::ofstream write_input("Input_DFT.dat");
        std::ofstream write_frequencies("Fre_DFT.dat");
        for (int i = 0; i < N; i++) //Prendre la première moitié de la fourier transform
        {
            write_output<<time[i]<<" ";
            write_input<<time[i]<<" ";
            write_input<<signalOrig[i]<<std::endl;
            write_frequencies << frequencies[i] << " ";
            //write_output<<frequencies[i]<<" ";
            //write_output<<signalDFT[i].real()<<std::endl;
            write_frequencies<<std::abs(signalDFT[i]) << std::endl;
            write_output<<signalRecov[i]<<std::endl;

        }
        for (int i = 0; i < frequencies.size(); ++i) {
            write_frequencies << frequencies[i] << " ";

            write_frequencies << std::abs(signalDFT[i]) << std::endl;
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