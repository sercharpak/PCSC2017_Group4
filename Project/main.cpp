//
// Created by shernand on 11/30/17.
//

#include "AudioFile.h"
#include "Signal.h"
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

int main(int argc, char* argv[]) {
    try {
        Signal Sign("./wav_mono_16bit_44100.wav");
        std::ofstream write_hist("Histogram.dat");
        Histogram(Sign, 50, write_hist);
        write_hist.close();
    }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
        return 1;
    }

    return 0;
}