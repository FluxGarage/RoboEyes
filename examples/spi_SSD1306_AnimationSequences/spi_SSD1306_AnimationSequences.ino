//***********************************************************************************************
//  This example shows how to create Robo Eyes animation sequences without the use of delay(); 
//
//  Hardware: You'll need a breadboard, an arduino nano r3, an SPI oled display with 1306   
//  or 1309 chip and some jumper wires.
//  
//  Published in August 2024 by Dennis Hoelscher, FluxGarage
//  www.youtube.com/@FluxGarage
//  www.fluxgarage.com
//
//***********************************************************************************************


#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Comment out above, uncomment this block to use hardware SPI
#define OLED_DC     11
#define OLED_CS     12
#define OLED_RESET  13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);
*/

#include <FluxGarage_RoboEyes.h>
roboEyes roboEyes; // create eyes

// EVENT TIMER
unsigned long eventTimer; // will save the timestamps
bool event0wasPlayed = 0; // flag variables
bool event1wasPlayed = 0;
bool event2wasPlayed = 0;
bool event3wasPlayed = 0;


void setup() {
  // Startup OLED Display
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Startup robo eyes
  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100); // screen-width, screen-height, max framerate - 60-100fps are good for smooth animations
  roboEyes.setPosition(DEFAULT); // eye position should be middle center
  roboEyes.close(); // start with closed eyes 
  
  eventTimer = millis(); // start event timer from here

} // end of setup


void loop() {
 roboEyes.update(); // update eyes drawings

  // LOOPED ANIMATION SEQUENCE
  // Do once after defined number of milliseconds
  if(millis() >= eventTimer+2000 && event1wasPlayed == 0){
    event1wasPlayed = 1; // flag variable to make sure the event will only be handled once
    roboEyes.open(); // open eyes 
  }
  // Do once after defined number of milliseconds
  if(millis() >= eventTimer+4000 && event2wasPlayed == 0){
    event2wasPlayed = 1; // flag variable to make sure the event will only be handled once
    roboEyes.setMood(HAPPY);
    roboEyes.anim_laugh();
    //roboEyes.anim_confused();
  }
  // Do once after defined number of milliseconds
  if(millis() >= eventTimer+6000 && event3wasPlayed == 0){
    event3wasPlayed = 1; // flag variable to make sure the event will only be handled once
    roboEyes.setMood(TIRED);
    //roboEyes.blink();
  }
  // Do once after defined number of milliseconds, then reset timer and flags to restart the whole animation sequence
  if(millis() >= eventTimer+8000){
    roboEyes.close(); // close eyes again
    roboEyes.setMood(DEFAULT);
    // Reset the timer and the event flags to restart the whole "complex animation loop"
    eventTimer = millis(); // reset timer
    event1wasPlayed = 0; // reset flags
    event2wasPlayed = 0;
    event3wasPlayed = 0;
  }
  // END OF LOOPED ANIMATION SEQUENCE

} // end of main loop