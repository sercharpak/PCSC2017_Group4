//
// Created by didier on 04/12/17.
//

//=======================================================================
/** @file Read.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 *
 * This classes are useful to generate a signal from different ways
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
    /** Method Construct */
    virtual Signal construct () = 0;

};
//IMPORTANT: THE FILE NAMES MUST BE IN ABSOLUTE

/** Class to read an audio file and construct a signal out of it
 */
class ReadAudioFile:public ConstructSignal{
private:
    /** Name of the audio file*/
    std::string name;
public:
    /** Constructor with the name of the audio file
     *
     * @param n name of audio file
     */
    ReadAudioFile(std::string n);

    /** Construct a signal from the audio file we loaded
     *
     * @return a signal constructed from an audio file loaded
     */
    virtual Signal construct() override;
};

/** Class to construct a signal out of a given frequency
 */
class ConstructFromFrequency: public ConstructSignal{
private:
    /** Frequency of the signal we want to construct */
    double frequency;
    double numSamples;
public:
    /** Constructor with the frequency
     *
     * @param f frequency
     */
    ConstructFromFrequency(double f, double n=352800.0);

    /** Construct the signal from the frequency
     *
     * @return a signal of given frequency
     */
    virtual Signal construct() override ;
};


/** Class to read an amplitude file and construct a signal out of it
 */
class ReadAmplitudeFile : public ConstructSignal{
private:
    /** Name of the file*/
    std::string name;
public:
    /** Constructor with the name of the file
     *
     * @param n name of file
     */
    ReadAmplitudeFile(std::string n);

    /** Construct a signal from the file we loaded
     *
     * @return a signal constructed from a file loaded
     */
    virtual Signal construct() override ;
};

#endif //PROJECT_READ_H
