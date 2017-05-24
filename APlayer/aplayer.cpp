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

#include "aplayer.h"

APlayer::APlayer(int pin, int stopButtonPin, ctrlFunPointer fun)
{
    pinMode(pin, OUTPUT);
    buzzerPin_= pin;
    fun_ = fun;
}

void APlayer::setControlFunction(ctrlFunPointer fun){
    fun_ = fun;
}

void APlayer::setStopButtonPin(int stopButtonPin){
    stopButtonPin_ = stopButtonPin;
}

void APlayer::play(int melody)
{
    if(melody == STAR_WARS){
        APlayer::swars();
        return;
    }
    
    if(melody == SUPER_MARIO){
        APlayer::smario();
        return;
    }
    
    if(melody == NYAN_CAT){
        APlayer::nyanc();
        return;
    }
    
    if(melody == TETRIS){
        APlayer::tetris();
        return;
    }
}

void APlayer::playNtimes(const int n, int melody)
{
    playWithStop_ = false;
    playWithControl_ = false;
    executionStop_ = false;
    
    for(int i = 0; i<n; ++i){
        APlayer::play(melody);
    }
}

void APlayer::playUntilStop(int melody)
{
    playWithStop_ = true;
    playWithControl_ = false;
    executionStop_ = false;
    
    while(!executionStop_){
        APlayer::play(melody);
    }

}

void APlayer::playUntilStopWithControl(int melody)
{
    playWithStop_ = true;
    playWithControl_ = true;
    executionStop_ = false;
    
    while(!executionStop_){
        APlayer::play(melody);
    }
}

void APlayer::play_section(int notes[], int tempo[], int times, int size)
{
    for (int i = 0; i < times && !executionStop_; ++i){
        for(int thisNote = 0; thisNote < size && !executionStop_; ++thisNote){
            // Play the note
            tone(buzzerPin_, notes[thisNote], tempo[thisNote]);
            
            // Delay to leave the buzzer the time to play the note (+ 1 to separate notes)
            delay(tempo[thisNote] + 1);
            
            // Check if stop button is pressed when necessary
            if(playWithStop_ && (stopButtonPin_ == -1 || digitalRead(stopButtonPin_) == HIGH)){
                executionStop_ = true;
            }
            
            // Execute control function when it is necessary
            if(playWithControl_ && fun_ != NULL){
                fun_();
            }
        }
    }
}

void APlayer::smario()
{
    // Super Mario duration of the notes
    #define SM_BPM 400        // --> Change this value if you want to change Super Mario's tempo
    #define SM_H 2*SM_Q       // half 2/4
    #define SM_Q 60000/SM_BPM // quarter 1/4
    #define SM_E SM_Q/2       // eighth 1/8
    #define SM_S SM_Q/4       // sixteenth 1/16
    #define SM_W 4*SM_Q       // whole 4/4
    #define SM_TW SM_W/3      // triplet "in 4/4"
    #define SM_TH SM_H/3      // triplet "of 2/4"
    
    // Super Mario OVERWORLD notes and tempo
    int smario_overworld_notes[] = {
        NOTE_E7, NOTE_E7, 0, NOTE_E7,
        0, NOTE_C7, NOTE_E7, 0,
        NOTE_G7, 0, 0,
        NOTE_G6, 0, 0,
        
        NOTE_C7, 0, 0, NOTE_G6,
        0, NOTE_E6, 0,
        0, NOTE_A6, 0, NOTE_B6,
        0, NOTE_AS6, NOTE_A6, 0,
        
        NOTE_G6, NOTE_E7, NOTE_G7,
        NOTE_A7, 0, NOTE_F7, NOTE_G7,
        0, NOTE_E7, 0, NOTE_C7,
        NOTE_D7, NOTE_B6, 0,
        
        NOTE_C7, 0, 0, NOTE_G6,
        0, NOTE_E6, 0,
        0, NOTE_A6, 0, NOTE_B6,
        0, NOTE_AS6, NOTE_A6, 0,
        
        NOTE_G6, NOTE_E7, NOTE_G7,
        NOTE_A7, 0, NOTE_F7, NOTE_G7,
        0, NOTE_E7, 0, NOTE_C7,
        NOTE_D7, NOTE_B6, 0
    };
    int smario_overworld_tempo[] = {
        SM_Q, SM_Q, SM_Q, SM_Q,
        SM_Q, SM_Q, SM_Q, SM_Q,
        SM_Q, SM_Q, SM_H,
        SM_Q, SM_Q, SM_H,
        
        SM_Q, SM_Q, SM_Q, SM_Q,
        SM_H, SM_Q, SM_Q,
        SM_Q, SM_Q, SM_Q, SM_Q,
        SM_Q, SM_Q, SM_Q, SM_Q,
        
        SM_TW, SM_TW, SM_TW,
        SM_Q, SM_Q, SM_Q, SM_Q,
        SM_Q, SM_Q, SM_Q, SM_Q,
        SM_Q, SM_Q, SM_H,
        
        SM_Q, SM_Q, SM_Q, SM_Q,
        SM_H, SM_Q, SM_Q,
        SM_Q, SM_Q, SM_Q, SM_Q,
        SM_Q, SM_Q, SM_Q, SM_Q,
        
        SM_TW, SM_TW, SM_TW,
        SM_Q, SM_Q, SM_Q, SM_Q,
        SM_Q, SM_Q, SM_Q, SM_Q,
        SM_Q, SM_Q, SM_H
    };
    
    
    // Super Mario UNDERWORLD notes and tempo
    int smario_underworld_notes[] = {
            NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
            NOTE_AS3, NOTE_AS4, 0,
            0,
            NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
            NOTE_AS3, NOTE_AS4, 0,
            0,
            NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
            NOTE_DS3, NOTE_DS4, 0,
            0,
            NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
            NOTE_DS3, NOTE_DS4, 0,
            0, NOTE_DS4, NOTE_D4, NOTE_CS4,
            NOTE_C4, NOTE_DS4,
            NOTE_D4, NOTE_GS3,
            NOTE_G3, NOTE_CS4,
            NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
            NOTE_GS4, NOTE_DS4, NOTE_B3,
            NOTE_AS3, NOTE_A3, NOTE_GS3,
            0,
            0,
            0
    };
    int smario_underworld_tempo[] = {
            SM_Q, SM_Q, SM_Q, SM_Q,
            SM_Q, SM_Q, SM_H,
            SM_W,
            SM_Q, SM_Q, SM_Q, SM_Q,
            SM_Q, SM_Q, SM_H,
            SM_W,
            SM_Q, SM_Q, SM_Q, SM_Q,
            SM_Q, SM_Q, SM_H,
            SM_W,
            SM_Q, SM_Q, SM_Q, SM_Q,
            SM_Q, SM_Q, SM_H,
            SM_H, SM_TH, SM_TH, SM_TH,
            SM_H, SM_H,
            SM_H, SM_H,
            SM_H, SM_H,
            SM_TH, SM_TH, SM_TH, SM_TH, SM_TH, SM_TH,
            SM_TW, SM_TW, SM_TW,
            SM_TW, SM_TW, SM_TW,
            SM_W,
            SM_W,
            SM_W
    };
    
    //Play Super Marios' Song
    play_section(smario_overworld_notes, smario_overworld_tempo, 2, SIZE(smario_overworld_notes)); //2x OVERWORLD
    play_section(smario_underworld_notes, smario_underworld_tempo, 1, SIZE(smario_underworld_notes)); //1x UNDERWORLD
    
}


void APlayer::swars()
{
    // Star Wars duration of the notes
    #define SW_BPM 120        // --> Change this value if you want to change Star Wars' tempo
    #define SW_H 2*SW_Q       // half 2/4
    #define SW_Q 60000/SW_BPM // quarter 1/4
    #define SW_E SW_Q/2       // eighth 1/8
    #define SW_S SW_Q/4       // sixteenth 1/16
    #define SW_W 4*SW_Q       // whole 4/4
    
    // Star Wars MAIN theme notes and tempo
    int swars_main_notes[] = {
        NOTE_A3, NOTE_A3, NOTE_A3, NOTE_F3, NOTE_C4,
        NOTE_A3, NOTE_F3, NOTE_C4, NOTE_A3,
        NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_C4,
        NOTE_GS3, NOTE_F3, NOTE_C4, NOTE_A3,
        NOTE_A4, NOTE_A3, NOTE_A3, NOTE_A4, NOTE_GS4, NOTE_G4,
        NOTE_FS4, NOTE_E4, NOTE_F4, 0, NOTE_AS3, NOTE_DS4, NOTE_D4, NOTE_CS4,
        NOTE_C4, NOTE_B3, NOTE_C4, 0, NOTE_F3, NOTE_GS3, NOTE_F3, NOTE_A3,
        NOTE_C4, NOTE_A3, NOTE_C4, NOTE_E4,
        NOTE_A4, NOTE_A3, NOTE_A3, NOTE_A4, NOTE_GS4, NOTE_G4,
        NOTE_FS4, NOTE_E4, NOTE_F4, 0, NOTE_AS3, NOTE_DS4, NOTE_D4, NOTE_CS4,
        NOTE_C4, NOTE_B3, NOTE_C4, 0, NOTE_F3, NOTE_GS3, NOTE_F3, NOTE_C4,
        NOTE_A3, NOTE_F3, NOTE_C4, NOTE_A3,
        0
    };
    int swars_main_tempo[] = {
        SW_Q, SW_Q, SW_Q, SW_E+SW_S, SW_S,
        SW_Q, SW_E+SW_S, SW_S, SW_H,
        SW_Q, SW_Q, SW_Q, SW_E+SW_S, SW_S,
        SW_Q, SW_E+SW_S, SW_S, SW_H,
        SW_Q, SW_E+SW_S, SW_S, SW_Q, SW_E+SW_S, SW_S,
        SW_S, SW_S, SW_E, SW_E, SW_E, SW_Q, SW_E+SW_S, SW_S,
        SW_S, SW_S, SW_E, SW_E, SW_E, SW_Q, SW_E+SW_S, SW_S,
        SW_Q, SW_E+SW_S, SW_S, SW_H,
        SW_Q, SW_E+SW_S, SW_S, SW_Q, SW_E+SW_S, SW_S,
        SW_S, SW_S, SW_E, SW_E, SW_E, SW_Q, SW_E+SW_S, SW_S,
        SW_S, SW_S, SW_E, SW_E, SW_E, SW_Q, SW_E+SW_S, SW_S,
        SW_Q, SW_E+SW_S, SW_S, SW_H,
        SW_H
    };

    // Play Star Wars Song
    play_section(swars_main_notes, swars_main_tempo, 1, SIZE(swars_main_notes)); //1x MAIN
}

void APlayer::nyanc()
{
    // Nyan Cat duration of the notes
    #define NC_BPM 120        // --> Change this value if you want to change Nyan Cat's tempo
    #define NC_H 2*NC_Q       // half 2/4
    #define NC_Q 60000/NC_BPM // quarter 1/4
    #define NC_E NC_Q/2       // eighth 1/8
    #define NC_S NC_Q/4       // sixteenth 1/16
    #define NC_W 4*NC_Q       // whole 4/4
    
    // Nyan Cat INTRO notes and tempo
    int nyanc_intro_notes[] = {
        NOTE_DS5, NOTE_E5, NOTE_FS5, 0, NOTE_B5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_FS5, NOTE_B5, NOTE_DS6, NOTE_E6, NOTE_DS6, NOTE_AS5, NOTE_B5, 0,
        NOTE_FS5, 0, NOTE_DS5, NOTE_E5, NOTE_FS5, 0, NOTE_B5, NOTE_CS6, NOTE_AS5, NOTE_B5, NOTE_CS6, NOTE_E6, NOTE_DS6, NOTE_E6, NOTE_CS6
    };
    int nyanc_intro_tempo[] = {
        NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S,
        NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S
    };
    
    // Nyan Cat PART_A notes and tempo
    int nyanc_partA_notes[]= {
        NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
        NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_CS4, NOTE_B3,
        NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4,
        NOTE_D4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4,
        NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
        NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_CS4, NOTE_B3,
        NOTE_DS4, NOTE_FS4, NOTE_GS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4,
        NOTE_D4, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_FS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_B3
    };
    int nyanc_partA_tempo[] = {
        NC_E, NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_E, NC_E, NC_E,
        NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S,
        NC_E, NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S,
        NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_E, NC_E, NC_E,
        NC_E, NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_E, NC_E, NC_E,
        NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S,
        NC_E, NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S,
        NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_E, NC_E, NC_E
    };
    
    // Nyan Cat PART_B notes and tempo
    int nyanc_partB_notes[] = {
        NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4,
        NOTE_B3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_E4, NOTE_DS4, NOTE_CS4, NOTE_B3, NOTE_E3, NOTE_DS3, NOTE_E3, NOTE_FS3,
        NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_FS3,
        NOTE_B3, NOTE_B3, NOTE_AS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_B3, NOTE_AS3,
        NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4,
        NOTE_B3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_E4, NOTE_DS4, NOTE_CS4, NOTE_B3, NOTE_E3, NOTE_DS3, NOTE_E3, NOTE_FS3,
        NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_FS3,
        NOTE_B3, NOTE_B3, NOTE_AS3, NOTE_B3, NOTE_FS3, NOTE_GS3, NOTE_B3, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_B3, NOTE_CS4
    };
    int nyanc_partB_tempo[] = {
        NC_E, NC_S, NC_S, NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S,
        NC_E, NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S,
        NC_E, NC_S, NC_S, NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S,
        NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_E, NC_E,
        NC_E, NC_S, NC_S, NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S,
        NC_E, NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S,
        NC_E, NC_S, NC_S, NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S,
        NC_E, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_S, NC_E, NC_E
    };
    
    // Play Nyan Cat Song
    play_section(nyanc_intro_notes, nyanc_intro_tempo, 1, SIZE(nyanc_intro_notes)); //1x INTRO
    play_section(nyanc_partA_notes, nyanc_partA_tempo, 1, SIZE(nyanc_partA_notes)); //1x PART_A
    play_section(nyanc_partB_notes, nyanc_partB_tempo, 1, SIZE(nyanc_partB_notes)); //1x PART_B
    play_section(nyanc_partA_notes, nyanc_partA_tempo, 1, SIZE(nyanc_partA_notes)); //1x PART_A
    play_section(nyanc_partB_notes, nyanc_partB_tempo, 1, SIZE(nyanc_partB_notes)); //1x PART_B
    
}

void APlayer::tetris(){

    // Tetris duration of the notes
    #define TT_BPM 150        // --> Change this value if you want to change Nyan Cat's tempo
    #define TT_H 2*TT_Q       // half 2/4
    #define TT_Q 60000/TT_BPM // quarter 1/4
    #define TT_E TT_Q/2       // eighth 1/8
    #define TT_S TT_Q/4       // sixteenth 1/16
    #define TT_W 4*TT_Q       // whole 4/4
    
    // Tetris MAIN notes and tempo
    int melody[] = {
        NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
        NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
        NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
        NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
        NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
        NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
        NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
        NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
        NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
        NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
        NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
        NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
        NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
        NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
        NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
        NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
        NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
        NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
        NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3,
        NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
        NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
        NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
        NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3,
        NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
        NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
        NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
        NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
        NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
        NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
        NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
        NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
        NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
        NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
        NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
        NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
        NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2,
        NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5,
        NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
        NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5,
        NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
        NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
        NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
        NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3,
        NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
        NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3,
        NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
        NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3,
        NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3
    };
    int noteDurations[] = {
        TT_E,TT_E,TT_E,TT_E,TT_E,TT_S,TT_S,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,
        TT_E,TT_Q,TT_E,TT_E,TT_S,TT_S,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_S,TT_S,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_Q,TT_Q,
        TT_E,TT_E,TT_E,TT_E,TT_E,TT_S,TT_S,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,
        TT_E,TT_Q,TT_E,TT_E,TT_S,TT_S,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_S,TT_S,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_Q,TT_Q,
        TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,
        TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,
        TT_E,TT_E,TT_E,TT_E,TT_E,TT_S,TT_S,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,
        TT_E,TT_Q,TT_E,TT_E,TT_S,TT_S,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_S,TT_S,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_Q,TT_Q,
        TT_E,TT_E,TT_E,TT_E,TT_E,TT_S,TT_S,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,
        TT_E,TT_Q,TT_E,TT_E,TT_S,TT_S,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_S,TT_S,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_Q,TT_Q,
        TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,
        TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E,TT_E
    };
    
    play_section(melody, noteDurations, 1, SIZE(melody));

}