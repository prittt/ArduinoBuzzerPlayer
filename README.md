# Arduino Buzzer Player

Arduino Buzzer Player (APlayer) is a simple as useful Arduino library to play 'music' with buzzer. The library helps you to manage stop buttons and 'background' control functions <i>i.e.</i> simple functions which can be executed when the song is played. The songs/melodies currently included are: 
<ul>
  <li>The main theme of Star Wars's imperial march (STAR_WARS);</li>
  <li>Super Marios' Overworld and Underworld themes (SUPER_MARIO); </li>
  <li>Tatris' theme A (TETRIS);</li>
  <li>Nyan Cat theme (NYAN_CAT);</li>
  <li>and ... add your own, contributions are welcome!!
</ul>

## What this Repo Contains?

<ul>
<li>This readme!</li>
<li>The APlayer library (<i>APlayer</i> folder)</li>
<li>An example sketch that explains how the APlayer could be used (<i>example.ino</i>)</li>
<li>An excel file which defines pitches used in the code (<i>pitches.xlsx</i>)</li>
</ul>

## How to Install APlayer Library? 

First you have to download this repo as a .zip file (and unzip it) or clone it with git. Then it is necessary to include the APlayer folder into the Arduino Library path using <u>one</u> of the two methods listed below.
<ol>
  <li>Include the library using the Arduino IDE:
    <ul>
      <li>Open the IDE</li>
      <li>Click to 'Sketch -> Include Library -> Add .ZIP Library' and select the APlayer folder just downloaded. Note that you have to include only the APlayer folder and not the all GitHub project</li>  
     </ul>
  </li>
  .. or ..
  <li> Add 'manually' the APlayer folder in the Arduino Library path.</li>
</ol> 

## How to Use APlayer? 

Once the APlayer is istalled you can use it in your project to play songs as alarm sounds or whatever you want. 

<code>

#include <aplayer.h> // Include the Arduino Buzzer Player library

#define BUZZER_PIN 10 // The pin which control your buzzer
#define BUTTON_PIN 11 // The pin on which a momentary button is connected

void myControlFunction(void){
  // This is an example of simple function to be executed in background when buzzer is playing music.
  // Note that this function must be shorter and simpler than possible, otherwise it will break the beat of the song

  // Control stuffs: 
  // We can for example get temperature from sensor and consequently set the state of a rele!
}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  APlayer myPlayer(BUZZER_PIN); // Create a player object specifying the buzzer's pin
  
  myPlayer.play(STAR_WARS); // Plays Star Wars theme once
  myPlayer.playNtimes(10, TETRIS); // Plays Tetris theme ten times

  myPlayer.setStopButtonPin(BUTTON_PIN); // Set the stop button bin
  myPlayer.playUntilStop(NYAN_CAT); // Plays the Nyan Cat theme until the momentary button on pin BUTTON_PIN
                                    // is pressed, if no stop button was set the song will be played in loop 
                                    // forever.

  myPlayer.setControlFunction(&myControlFunction); // Set the 'background' function
  myPlayer.playUntilStopWithControl(SUPER_MARIO); // Plays Super Mario theme until the momentary button on pin 
                                                  // BUTTON_PIN is pressed, as for the playUntilStop method, if 
                                                  // no stop button was set the song will be played in loop forever.
                                                  // Moreover, after each note the 'control' function will be 
                                                  // executed.
  
}

</code>
