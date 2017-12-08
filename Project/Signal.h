//
// Created by didier on 02/12/17.
//

#ifndef PROJECT_SIGNAL_H
#define PROJECT_SIGNAL_H

#include <complex>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <utility> //For the function swap
#include <iostream>

#include "AudioFile.h"


class Signal{
private:
    std::vector<double> time;
    std::vector<std::complex<double>> FourierTransform;
    std::vector<int> Frequencies;
    std::vector<double> sample;
    //AudioFile<double> audioFile;
public:
    /** Constructors */
    Signal(AudioFile<double> audio);
    Signal(std::vector<double> sam);
    Signal();

    /** Destructor */
    ~Signal();


    /** Getters */
    std::vector<double> getTime() const;
    std::vector<double> getSamples() const;
    std::vector<std::complex<double>> getFourierTransform() const;
    std::vector<int> getFrequencies() const;

    /** Histogramm */
    void Histogram(int number_bin,std::ofstream& file) ;
    /** Fourier Transform
     *
     * Compute the Fourier transform of the signal
     * @param min_frequency The minimum frequency where we start to compute the Fourier transform
     * @param max_frequency The maximum frequency where we stop the computation of the Fourier transform
     * @param file A file in which the user wants to store the Fourier transform modulus
    */
    void FourierTransformCalculator(int min_frequency, int max_frequency, std::ofstream& file);

    /** Fourier Transform (no file saved)
     *
     * Compute the Fourier transform of the signal
     * @param min_frequency The minimum frequency where we start to compute the Fourier transform
     * @param max_frequency The maximum frequency where we stop the computation of the Fourier transform
    */
    void FourierTransformCalculator(int min_frequency, int max_frequency);

    /** Save the signal sample and time in a file
     * @param file The file in which we want to put the signal
     */
    void SaveSignal(std::ofstream& file);

    /** Compute the inverse Fourier Transform
     */
    void InverseFourierTransform();

    /** Write the signal inside a sound file
     *
     * @param FileName name of the sound file inside we want to put the signal
     */
    void WriteSound(std::string FileName);

};

#endif //PROJECT_SIGNAL_H
