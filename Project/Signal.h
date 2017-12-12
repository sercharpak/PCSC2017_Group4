<<<<<<< HEAD
=======
//
// Created by didier on 02/12/17.
//
>>>>>>> ea9a947fad4d3e1db52fd9a7c8b5a7a288dbed85
//=======================================================================
/** @file Signal.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 * Signal is the core class of the program. It contains the raw sound signals and the
 * Fourier Transform related methods. It can also computes the histogram of the signal
 * and perform the i/o taks for a sound file.
 *
 */
//=======================================================================

#ifndef PROJECT_SIGNAL_H
#define PROJECT_SIGNAL_H

#include <complex>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <utility> //For the function swap
#include <iostream>
#include <cmath>

#include "AudioFile.h"


/** Class to create and handle a signal.
 */
class Signal{
private:

    /** Samples
     */
    std::vector<double> sample;
    /** Time of the sample.
     */
    std::vector<double> time;
    /** Sample rate of the signal
     */
    double sampleRate;

    /** Fourier Transform .
     */
    std::vector<std::complex<double>> FourierTransform;

    /** Frequencies of the Fourier Transform.
     */
    std::vector<int> Frequencies;

public:

    /** Default Constructor of the compiler.
     */
    Signal() = default;

    /** Constructor using an AudioFile. The Fourier transform is not calculated.
     *
     * @param audio AudioFile<double> containing an audio file.
     */
    Signal(AudioFile<double> audio);

    /** Constructor using a vector of samples.
     *
     * @param sam std::vector<double> containing the samples.
     */
    Signal(std::vector<double> sam,double samRate=44100);


    /** Default destructor
     */
    ~Signal();


    /** Getter for the vector time.
    *
    * @return std::vector<double> time
    */
    std::vector<double> getTime() const;

    /** Getter for the vector of samples.
     *
     * @return std::vector<double> sample
     */
    std::vector<double> getSamples() const;

    /** Getter for the Fourier Transform.
     *
     * @return std::vector<std::complex<double>> FourierTransform
     */
    std::vector<std::complex<double>> getFourierTransform() const;

    /** Getter for the Frequencies.
     *
     * @return std::vector<double> Frequencies
     */
    double getSampleRate() const;

    /** Getter for the sample rate.
     *
     * @return double sample rate
     */
    std::vector<int> getFrequencies() const;

    /** Histogram
     *
     * Compute the histogram of the signal.
     * @param number_bin int which represents the number of bins we want in the histogram.
     * @param file std::ofstream in which we store the histogram and the corresponding bins
     */
    void Histogram(int number_bin,std::string fileName) ;
    /** Fourier Transform
     *
     * Compute the Fourier transform of the signal.
     * @param min_frequency int which represents the minimum frequency where we start to compute the Fourier transform.
     * @param max_frequency in which represents the maximum frequency where we stop the computation of the Fourier transform.
     * @param file std::ofstream in which we store the Fourier transform modulus and the corresponding frequencies.
    */
    void FourierTransformCalculator(int min_frequency, int max_frequency, std::string fileName);

    /** Fourier Transform (no file saved)
     *
     * Compute the Fourier transform of the signal.
     * @param min_frequency The minimum frequency where we start to compute the Fourier transform.
     * @param max_frequency The maximum frequency where we stop the computation of the Fourier transform.
    */
    void FourierTransformCalculator(int min_frequency, int max_frequency);

    /** Save the signal sample and time in a file
     * @param fileName std::string the filename of the file in which we want to store the samples and the time.
     */
    void SaveSignal(std::string fileName);

    /** Compute the inverse Fourier Transform.
     *
     * @param fileName  string which gives the name of the file inside we want to store the inverse fourier transform.
     */
    std::vector<double> InverseFourierTransform(std::string fileName);

    /** Write the signal inside a sound file.
     *
     * @param fileName  string which gives the name of the sound file inside we want to store the signal.
     */
    void WriteSound(std::string fileName);



};

/** Concatenation of two signals
     *
     * @param S1 Signal which is the first we want to concatenate.
     * @param S2 Signal which we want to write after S1.
     */

Signal concatenate(const Signal& S1,const Signal& S2);

#endif //PROJECT_SIGNAL_H
