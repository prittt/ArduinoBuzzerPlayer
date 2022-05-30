// Copyright(c) 2016 - Federico Bolelli
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// * Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and / or other materials provided with the distribution.
//
// * Neither the name of "aplayer (Arduino Audio Player)" nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef aplayer_h
#define aplayer_h

#include <Arduino.h>
#include "utilities/pitches.h"

#define SIZE(x) sizeof(x)/sizeof(*x)

// List of available melodies
enum melodies {
    STAR_WARS = 1,
    SUPER_MARIO = 2,
    NYAN_CAT = 3,
    TETRIS = 4,
    ALARM = 5
};

typedef void (*ctrlFunPointer)(void);

class APlayer
{
  public:
    // Constructor
    APlayer(int pin, int stopPin = -1, const ctrlFunPointer fun = NULL);
    
    // Setter
    void setControlFunction(const ctrlFunPointer fun);
    void setStopButtonPin(int stopButtonPin);
    
    // Play melodies functions
    void play(int melody);  // Play the specified melody/song one time
    void playNtimes(int n, int melody);  // Play the specified melody/song n times
    void playUntilStop(int melody);  // Play the specified melody until the "stopButtonPin" is pressed (if it is not set/specified the song will be played in loop forever)
    void playUntilStopWithControl(int melody);  // Play the specified melody until the "stopButtonPin" as "playUntilStop". Moreover it will execute the specified control function if any.
    
  private:
    void play_section(int notes[], int tempo[], int times, int size);
    
    // Songs
    void swars();
    void nyanc();
    void smario();
    void tetris();
    void alarm();
    
    // To control PIN
    int buzzerPin_;
    int stopButtonPin_;

    // Pointer to function which must be execute in "background"
    ctrlFunPointer fun_;
    
    // Bool function to handle cases
    bool playWithStop_;
    bool playWithControl_;
    bool executionStop_;

};

#endif

