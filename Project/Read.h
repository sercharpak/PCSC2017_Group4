//=======================================================================
/** @file Read.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * These classes are useful to generate a signal from different ways.
 * We can generate a signal from an AudioFile.
 * We can generate a signal from a specific frequency.
 * We can generate a signal from a file containing the samples and the time of the signal.
 *
 */
//=======================================================================

#ifndef PROJECT_READ_H
#define PROJECT_READ_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Signal.h"

/** Virtual abstract class which defines a standard construction of a signal.
 */
class ConstructSignal {
public:
    /** Construct method
     * pure virtual method provide to construct a signal.
     *
     * @return Signal
     * */
    virtual Signal construct () = 0;

};
//IMPORTANT: THE FILE NAMES MUST BE IN ABSOLUTE

/** Class to read an audio file and construct a signal out of it.
 */
class ReadAudioFile:public ConstructSignal{
private:
    /** Name (and absolute path) of the audio file (and the absolute path).
     */
    std::string name;
public:
    /** Constructor with the name of the audio file.
     *
     * @param n string which is name (and absolute path) of audio file (and the absolute path).
     */
    ReadAudioFile(std::string n);

    /** Construct a signal from the audio file we loaded.
     *
     * @return Signal which is constructed from an audio file loaded.
     */
    virtual Signal construct() override;
};

/** Class to construct a signal from a given frequency.
 */
class ConstructFromFrequency: public ConstructSignal{
private:
    /** Frequency of the signal we want to construct. */
    double frequency;

    /** Number of samples we want in the sample.
     */
    double numSamples;
public:
    /** Constructor with the frequency and the number of sample.
     *
     * @param f double which is the frequency.
     * @param n double which is the number of sample (default = 352800.0).
     */
    ConstructFromFrequency(double f, double n=352800.0);

    /** Construct the signal from the frequency.
     *
     * @return Signal construct from a given frequency.
     */
    virtual Signal construct() override ;
};


/** Class to read an amplitude file and construct a signal out of it.
 */
class ReadAmplitudeFile : public ConstructSignal{
private:
    /** Name (and absolute path) of the file (and the absolute path).
     */
    std::string name;

public:
    /** Constructor with the name (and absolute path) of the file.
     *
     * @param n std::string name of file (and absolute path).
     */
    ReadAmplitudeFile(std::string n);

    /** Construct a signal from the file of samples we loaded.
     *
     * @return Signal constructed from a file of samples loaded.
     */
    virtual Signal construct() override ;
};

#endif //PROJECT_READ_H
