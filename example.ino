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
