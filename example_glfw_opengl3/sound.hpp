#pragma once

#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"
inline SoLoud::Soloud gSoloud; // SoLoud engine
inline SoLoud::Wav gWave;      // One wave file
inline SoLoud::Wav gWave2;      // One wave file
namespace sound {
    void init() {
        gSoloud.init();
        gWave.load("LoudSelect.wav");
        gWave2.load("QuietLoad.wav");
    }
    void play() {
        gSoloud.play(gWave);
    }
    void play2() {
        gSoloud.play(gWave2);
    }
};