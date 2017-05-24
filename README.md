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

void setup{
  
}

</code>
