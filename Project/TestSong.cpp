//
// Created by didier on 08/12/17.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <complex>

#include "AudioFile.h"
#include "Signal.h"
#include "Read.h"

/*This file is to test if the creation of a signal from a frequency is working correctly and also if the saving of the
 * sound into a file.wav is correct
 *
 * In order to do that, I generate three signals from 3 different frequenceies and then concatenate the signals
 * together and save the result into a file.
 *
*/

int main(int argc, char* argv[]) {

    //Construct the signal from the frequency for DO, RE, MI
    ConstructFromFrequency DO_Note(261.63, 88200);
    ConstructFromFrequency RE_Note(293.66, 88200);
    ConstructFromFrequency MI_Note(329.63, 88200);

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
    Song = concatenate(Song,RE_NoteSignal);
    Song = concatenate(Song, DO_NoteSignal);

    std::string songFourier ="SongFourier.dat";
    Song.FourierTransformCalculator(0,400,songFourier);

    // Finally I wrote the signal in a sound file.
    Song.WriteSound("Song.wav");

    return 0;
}