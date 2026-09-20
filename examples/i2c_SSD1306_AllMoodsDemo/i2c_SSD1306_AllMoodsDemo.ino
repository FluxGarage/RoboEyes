//***********************************************************************************************
//  This example demonstrates all available mood expressions (emotions) of the FluxGarage
//  Robo Eyes library.
//
//  The eyes cycle through every mood with smooth transitions between them. A mood is shown
//  for a few seconds before the next one starts.
//
//  Hardware: an Arduino Nano, an I2C OLED display with SSD1306 (or SSD1309) chip and jumper
//  wires.
//
//  All moods:
//  DEFAULT, TIRED, ANGRY, HAPPY, ALERT, BORED, DESPAIR, DISORIENTED, EXCITED, FOCUSED,
//  FURIOUS, SAD, SCARED, SLEEPY, SURPRISED, WORRIED, ANNOYED, CONFUSED, CURIOUS, PROUD,
//  RELAXED
//
//***********************************************************************************************


#include <Adafruit_SSD1306.h>
#include <FluxGarage_RoboEyes.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// create a RoboEyes instance using an Adafruit_SSD1306 display driver
RoboEyes<Adafruit_SSD1306> roboEyes(display);

// List of all moods to cycle through
const unsigned char moods[] = {
  DEFAULT, TIRED, ANGRY, HAPPY, ALERT, BORED, DESPAIR, DISORIENTED, EXCITED,
  FOCUSED, FURIOUS, SAD, SCARED, SLEEPY, SURPRISED, WORRIED, ANNOYED,
  CONFUSED, CURIOUS, PROUD, RELAXED
};

byte moodIndex = 0;           // current mood index
unsigned long moodTimer = 0;  // timer for mood switching
int moodShowDuration = 4000;  // how long each mood is shown, in milliseconds


void setup() {
  Serial.begin(9600);

  // Startup OLED Display
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C or 0x3D
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Startup robo eyes
  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100); // screen-width, screen-height, max framerate
  roboEyes.setPosition(DEFAULT); // eyes start centered
  roboEyes.setMood(moods[moodIndex]); // first mood
  moodTimer = millis();

  Serial.println(F("RoboEyes mood demo started"));

} // end of setup


void loop() {
  roboEyes.update(); // update eyes drawings (framerate limited)

  // Cycle through moods whenever the show duration has passed
  if (millis() >= moodTimer + moodShowDuration){
    moodIndex++;
    if (moodIndex >= sizeof(moods)){moodIndex = 0;} // wrap around
    roboEyes.setMood(moods[moodIndex]); // switch to next mood, transitions are smooth
    moodTimer = millis();
    Serial.print(F("Mood: "));
    Serial.println(moods[moodIndex]);
  }
} // end of loop