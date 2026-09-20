//***********************************************************************************************
//  This example shows how to combine the mood expressions with gaze directions
//  (look up, look down, look left, look right) using the setPosition() method.
//
//  Every gaze direction is shown together with a fitting emotion, then the eyes cycle
//  through all remaining moods while looking around.
//
//  Hardware: an Arduino Nano, an I2C OLED display with SSD1306 (or SSD1309) chip and jumper
//  wires.
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

// Look-direction demo steps: mood + position
// look up (N), look down (S), look left (W), look right (E)
const unsigned char lookMoods[] = { SURPRISED, SLEEPY, WORRIED, ALERT };
const unsigned char lookPositions[] = { N, S, W, E };
byte lookIndex = 0;

// After the look steps, cycle through all remaining moods centered
const unsigned char moods[] = {
  DEFAULT, TIRED, ANGRY, HAPPY, ALERT, BORED, DESPAIR, DISORIENTED, EXCITED,
  FOCUSED, FURIOUS, SAD, SCARED, SLEEPY, SURPRISED, WORRIED, ANNOYED,
  CONFUSED, CURIOUS, PROUD, RELAXED
};
byte moodIndex = 0;

unsigned long stepTimer = 0;
int stepDuration = 3000; // how long each step is shown, in milliseconds
byte step = 0; // 0..3 = look steps, 4+ = centered mood cycling


void setup() {
  Serial.begin(9600);

  // Startup OLED Display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Startup robo eyes
  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);
  roboEyes.setPosition(DEFAULT);
  stepTimer = millis();

} // end of setup


void loop() {
  roboEyes.update();

  // advance to the next demo step whenever the step duration has passed
  if (millis() >= stepTimer + stepDuration){
    stepTimer = millis();

    if (step < 4){
      // Look-direction steps: combine a mood with a gaze direction
      roboEyes.setMood(lookMoods[step]);
      roboEyes.setPosition(lookPositions[step]);
      step++;
    } else {
      // Centered mood cycling
      roboEyes.setPosition(DEFAULT);
      roboEyes.setMood(moods[moodIndex]);
      moodIndex = (moodIndex + 1) % (sizeof(moods)/sizeof(moods[0])); // wrap around
    }
  }
} // end of loop