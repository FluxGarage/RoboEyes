# FluxGarage RoboEyes Library

Draws smoothly animated robot eyes on OLED displays, using the Adafruit GFX library. Robot eye shapes are configurable in terms of width, height, border radius and space between. Several different mood expressions (happy, tired, angry, default) and animations (autoblinker, idle, laughing, confused) are available. All state changes have smooth transitions and thus, complex animation sequences are easily feasible.

Developing this library was the first step of a larger project: the creation of my own DIY robot from the design perspective. Check out the [FluxGarage Youtube Channel](https://www.youtube.com/@FluxGarage).


## Watch the Demo and Getting Started Videos on Youtube

[![#1 - Smoothly Animated Robot Eyes on OLED Displays with the Robo Eyes Library](https://img.youtube.com/vi/ibSaDEkfUOI/0.jpg)](https://www.youtube.com/watch?v=ibSaDEkfUOI)
[![#2 - Getting Started With the Free Robo Eyes Arduino Library](https://img.youtube.com/vi/WtLWc5zzrmI/0.jpg)](https://www.youtube.com/watch?v=WtLWc5zzrmI)


## Installation

1. Navigate to [github.com/FluxGarage/RoboEyes](https://github.com/FluxGarage/RoboEyes).
2. Choose "Code > Download Zip"
3. In the Arduino IDE, navigate to "Sketch > Include Library > Add .ZIP Library" and select the downloaded file


## Functions

### General
- **begin()** _(screen-width, screen-height, max framerate)_
- **update()** _update eyes drawings in the main loop, limited by max framerate as defined in begin()_
- **drawEyes()** _same as update(), but without the framerate limitation_
  
### Define Eye Shapes, all values in pixels
- **setWidth()** _(byte leftEye, byte rightEye)_
- **setHeight()** _(byte leftEye, byte rightEye)_
- **setBorderradius()** _(byte leftEye, byte rightEye)_
- **setSpacebetween()** _(int space) -> can also be negative_
- **setCyclops()** _(bool ON/OFF) -> if turned ON, robot has only on eye_

### Define Face Expressions (Mood, Curiosity, Eye-Position, Open/Close)
- **setMood()** _mood expression, can be TIRED, ANGRY, HAPPY, DEFAULT_
- **setPosition()** _cardinal directions, can be N, NE, E, SE, S, SW, W, NW, DEFAULT (default = horizontally and vertically centered)_
- **setCuriosity()** _(bool ON/OFF) -> when turned on, height of the outer eyes increases when moving to the very left or very right_
- **open()** _open both eyes -> open(1,0) opens left eye only_
- **close()** _close both eyes -> close(1,0) closes left eye only_

### Set Horizontal and/or Vertical Flicker
Alternately displaces the eyes in the defined amplitude in pixels:
- **setHFlicker()** _(bool ON/OFF, byte amplitude)_
- **setVFlicker()** _(bool ON/OFF, byte amplitude)_

### Play Prebuilt Oneshot Animations
- **anim_confused()** _confused -> eyes shaking left and right_
- **anim_laugh()** _laughing -> eyes shaking up and down_
- **blink()** _close and open both eyes_
- **blink(0,1)** _close and open right eye_

### Macro Animators
Blinks both eyes randomly:
- **setAutoblinker()** _(bool ON/OFF, int interval, int variation) -> turn on/off, set interval between each blink in full seconds, set range for additional random interval variation in full seconds_

Repositions both eyes randomly:
- **setIdleMode()** _(bool ON/OFF, int interval, int variation) -> turn on/off, set interval between each eye repositioning in full seconds, set range for additional random interval variation in full seconds_

