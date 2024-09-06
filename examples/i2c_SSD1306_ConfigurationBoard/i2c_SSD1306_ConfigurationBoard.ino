//***********************************************************************************************
//  Code for the Robo Eyes configuration board as shown in the first video:
//  https://youtu.be/ibSaDEkfUOI
//
//  The configuration board enables you to configure your preferred eye shapes and play around 
//  with the library's mood types and animations - you just need a breadboard, an arduino nano, 
//  some pushbuttons, jumper wires and optionally a joystick module. Find the instructions here:
//  http://www.instructables.com/member/FluxGarage/
//  
//  Published in September 2024 by Dennis Hoelscher, FluxGarage
//  www.youtube.com/@FluxGarage
//  www.fluxgarage.com
//
//***********************************************************************************************

#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <FluxGarage_RoboEyes.h>
roboEyes roboEyes; // create eyes

#include <Pushbutton.h> // Pushbutton library by Pololu, can be found in the Arduino library manager

// Create buttons and define their pins
Pushbutton buttonMood(5); // Change mood types
Pushbutton buttonLaugh(6); // Trigger laugh animation
Pushbutton buttonConfused(7); // Trigger confused animation
Pushbutton buttonFlicker(8); // Toggle flicker animation
Pushbutton buttonConfigMode(9); // Configuration mode
Pushbutton buttonIncrement(10); // Configuration increment
Pushbutton buttonDecrement(11); // Configuration decrement
Pushbutton buttonJoystick(12); // Joystick button - switch between idle mode (automatic random eye positions) and joystick mode (manual control of eye positions with joystick)

// Joystick pins
int joystickXpin = A0;
int joystickYpin = A1;
// For toggling the reading of the joystick
bool joystickToggle = 0;

// For setting mood expression and eye position
byte mood = 0; // Mood switch
byte position = 0; // Position switch

// Name aliases for different config mode states
#define EYES_WIDTHS 0
#define EYES_HEIGHTS 1
#define EYES_BORDERRADIUS 2
#define EYES_SPACEBETWEEN 3
#define CYCLOPS_TOGGLE 4
#define CURIOUS_TOGGLE 5
#define PREDEFINED_POSITIONS 6
byte configMode = 6; // for saving current config mode state
bool showConfigMode = 0; // for showing current config mode on display
unsigned long showConfigModeTimer = 0;
int showConfigModeDuration = 1500; // how long should the current config mode headline be displayed?


void setup() {

  //Serial.begin(9600); // Serial might not work properly, probably due to exhausted memory capacity when using ATMEGA328P based boards

  // Initialize OLED display
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C or 0x3D
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Startup robo eyes
  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100); // screen-width, screen-height, max framerate
  roboEyes.close(); // start with closed eyes 
  roboEyes.setPosition(DEFAULT); // eyes should be initially centered

  // Define eyes behaviour for demonstration
  roboEyes.setAutoblinker(ON, 3, 2); // Start auto blinker animation cycle -> bool active, int interval, int variation -> turn on/off, set interval between each blink in full seconds, set range for random interval variation in full seconds
  roboEyes.setIdleMode(ON, 3, 1); // Start idle animation cycle (eyes looking in random directions) -> set interval between each eye repositioning in full seconds, set range for random time interval variation in full seconds

  //display.invertDisplay(true); // show inverted display colors (black eyes on bright background)

} // end of setup


void loop() {
  if (!showConfigMode){
    roboEyes.update();  // Updates eye drawings limited by max framerate (good for fast controllers to limit animation speed). 
                        // If you want to use the full horsepower of your controller without limits, you can use drawEyes(); instead.
  } else {
    // Show current config mode headline in display
    display.clearDisplay(); // clear screen
    // Basic text setup for displaying config mode headlines
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,3);
    if(configMode == EYES_WIDTHS){
      display.println("Widths"); 
      display.println(roboEyes.eyeLwidthCurrent);
      }
    else if(configMode == EYES_HEIGHTS){
      display.println("Heights"); 
      display.println(roboEyes.eyeLheightCurrent);
      }
    else if(configMode == EYES_BORDERRADIUS){
      display.println("Border \nRadius"); 
      display.println(roboEyes.eyeLborderRadiusCurrent);
      }
    else if(configMode == EYES_SPACEBETWEEN){
      display.println("Space \nBetween"); 
      display.println(roboEyes.spaceBetweenCurrent);
      }
    else if(configMode == CYCLOPS_TOGGLE){
      display.println("Cyclops \nToggle");
      }
    else if(configMode == CURIOUS_TOGGLE){
      display.println("Curiosity \nToggle");
      }
    else if(configMode == PREDEFINED_POSITIONS){
      display.println("Predefined\nPositions"); 
      roboEyes.setIdleMode(0); // turn off idle mode
      roboEyes.setPosition(DEFAULT); // start with middle centered eyes
      }
    display.display(); // additionally show configMode on display
    if(millis() >= showConfigModeTimer+showConfigModeDuration){
      showConfigMode = 0; // don't show the current config mode on the screen anymore
    }
  }

  readButtons();

  if (joystickToggle){
    readJoystick();
  }

} // end of main loop


// Read joystick and map eye position accordingly
void readJoystick(){
  int joystickX = analogRead(joystickXpin);
  int joystickY = analogRead(joystickYpin);
  roboEyes.eyeLxNext = map(joystickX, 0, 1023, 0, roboEyes.getScreenConstraint_X() );
  roboEyes.eyeLyNext = map(joystickY, 0, 1023, 0, roboEyes.getScreenConstraint_Y() );
} // end of readJoystick


// Read all buttons
void readButtons(){
  // MOOD TYPES
  // choose between different mood type expressions
  if (buttonMood.getSingleDebouncedPress()){
    if (mood<3){mood++;} else{mood=0;}
    if (mood==0){roboEyes.setMood(DEFAULT);}
    else if (mood==1){roboEyes.setMood(TIRED);}
    else if(mood==2){roboEyes.setMood(ANGRY);}
    else if(mood==3){roboEyes.setMood(HAPPY);}
  }

  // PLAY LAUGH ANIMATION
  if (buttonLaugh.getSingleDebouncedPress()){
    roboEyes.anim_laugh(); // trigger animation "laugh"
  }

  // PLAY CONFUSED ANIMATION
  if (buttonConfused.getSingleDebouncedPress()){
    roboEyes.anim_confused(); // trigger animation "confused"
  }

  // ADD HORIZONTAL FLICKER: TURN ON WHEN PRESSED, TURN OFF WHEN RELEASED
  if (buttonFlicker.getSingleDebouncedPress()){
    roboEyes.setHFlicker(ON, 1); // bool flickerBit, byte Amplitude -> Turn on/off, set horizontal amplitude in px
  } 
  if (buttonFlicker.getSingleDebouncedRelease()){
    roboEyes.setHFlicker(OFF); // turn off
  } 

  // EYES GEOMETRY CONFIGURATION
  if (buttonConfigMode.getSingleDebouncedPress()){
    if(configMode<6){configMode++;}
    else {configMode=0;}
    showConfigMode = 1;
    showConfigModeTimer = millis();
  }
  if (buttonIncrement.getSingleDebouncedPress()){
    showConfigMode = 0; // don't show the current config mode on the screen anymore
    if(configMode == EYES_WIDTHS){roboEyes.eyeLwidthNext++; roboEyes.eyeRwidthNext++;}
    else if(configMode == EYES_HEIGHTS){roboEyes.eyeLheightNext++; roboEyes.eyeRheightNext++; roboEyes.eyeLheightDefault++; roboEyes.eyeRheightDefault++;}
    else if(configMode == EYES_BORDERRADIUS){
      if(roboEyes.eyeLborderRadiusNext<50){roboEyes.eyeLborderRadiusNext++;}
      if(roboEyes.eyeRborderRadiusNext<50){roboEyes.eyeRborderRadiusNext++;}
      }
    else if(configMode == EYES_SPACEBETWEEN){roboEyes.spaceBetweenNext++;}
    else if(configMode == CYCLOPS_TOGGLE){roboEyes.setCyclops(OFF);} // no cyclops mode
    else if(configMode == CURIOUS_TOGGLE){roboEyes.setCuriosity(ON);} // curious mode
    else if(configMode == PREDEFINED_POSITIONS){
      if (position<8){position++;} else{position=0;}
      updatePosition();
    }
  }
  if (buttonDecrement.getSingleDebouncedPress()){
    showConfigMode = 0; // don't show the current config mode on the screen anymore
    if(configMode == EYES_WIDTHS){roboEyes.eyeLwidthNext--; roboEyes.eyeRwidthNext--;}
    else if(configMode == EYES_HEIGHTS){roboEyes.eyeLheightNext--; roboEyes.eyeRheightNext--; roboEyes.eyeLheightDefault--; roboEyes.eyeRheightDefault--;}
    else if(configMode == EYES_BORDERRADIUS){
      if(roboEyes.eyeLborderRadiusNext>0){roboEyes.eyeLborderRadiusNext--;}
      if(roboEyes.eyeRborderRadiusNext>0){roboEyes.eyeRborderRadiusNext--;}
      }
    else if(configMode == EYES_SPACEBETWEEN){roboEyes.spaceBetweenNext--;}
    else if(configMode == CYCLOPS_TOGGLE){roboEyes.setCyclops(ON);} // cyclops mode
    else if(configMode == CURIOUS_TOGGLE){roboEyes.setCuriosity(OFF);} // no curious mode
    else if(configMode == PREDEFINED_POSITIONS){
      if (position>0){position--;} else{position=8;}
      updatePosition();
    }
  }

  // JOYSTICK BUTTON
  // toggles between joystick controlled eye position and idle animation (eyes looking in random directions)
  if (buttonJoystick.getSingleDebouncedPress()){
    joystickToggle = !joystickToggle;
    roboEyes.idle = !roboEyes.idle;
  }


} // end of readButtons

// Using predefined positions
void updatePosition(){
  if (position==0){roboEyes.setPosition(DEFAULT);}
    else if(position==1){roboEyes.setPosition(N);}
    else if(position==2){roboEyes.setPosition(NE);}
    else if(position==3){roboEyes.setPosition(E);}
    else if(position==4){roboEyes.setPosition(SE);}
    else if(position==5){roboEyes.setPosition(S);}
    else if(position==6){roboEyes.setPosition(SW);}
    else if(position==7){roboEyes.setPosition(W);}
    else if(position==8){roboEyes.setPosition(NW);}
} // end of updatePosition
