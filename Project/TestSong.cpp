//=======================================================================
/** @file TestSong.cpp
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing.
 *
 * This file is to test if the creation of a signal from a frequency is working correctly and also if the saving of the
 * sound into a file.wav is correct.
 *
 * In order to do that, I generate three signals from 3 different frequencies and then concatenate the signals
 * together and save the result into a file.
 *
 * BE CAREFUL: THIS TEST TAKES TIME DUE TO THE FOURIER TRANSFORM!
 *
*/
//=======================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <complex>

#include "AudioFile.h"
#include "Signal.h"
#include "Read.h"



int main(int argc, char* argv[]) {

    //Construct the signal from the frequency for DO, RE, MI
    ConstructFromFrequency DO_Note(261.63, 11025);
    ConstructFromFrequency RE_Note(293.66, 11025);
    ConstructFromFrequency MI_Note(329.63, 11025);

    Signal DO_NoteSignal;
    Signal RE_NoteSignal;
    Signal MI_NoteSignal;
    DO_NoteSignal = DO_Note.construct();
    RE_NoteSignal = RE_Note.construct();
    MI_NoteSignal = MI_Note.construct();

    // Create the signal song by concatening the three signals.
    Signal Song;

    Song = concatenate(DO_NoteSignal, RE_NoteSignal);
    Song = concatenate(Song, MI_NoteSignal);

    std::string songFourier ="SongFourier.dat";
    Song.writeFourier(songFourier);

    // Finally I wrote the signal in a sound file.
    Song.writeSound("Song.wav");

    return 0;
}