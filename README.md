# RoboEyesWink - FluxGarage RoboEyes Library (Extended)

Draws smoothly animated robot eyes on OLED displays, using the Adafruit GFX library. Robot eye shapes are configurable in terms of width, height, border radius and space between. **21 different mood expressions** (emotions), gaze directions (look up/down/left/right + diagonals) and animations (autoblinker, idle, laughing, confused, sweat drops, flickering) are available. All state changes have **smooth, fluid transitions** — the eye geometry, eyelid shapes and positions are tweened frame-by-frame, so complex emotion sequences are easily feasible.

This is an extended fork of the original **FluxGarage RoboEyes** library by Dennis Hoelscher — the API is fully backward-compatible, so all original sketches keep working. New: 17 additional moods, fluid frame-by-frame transitions, mood-specific eye geometry (rounded/wide/narrow eyes), mood-induced sweat drops and a helper for fluid one-shot animations.

Developing this library was the first step of a larger project: the creation of my own DIY robot from the design perspective. Check out the [FluxGarage Youtube Channel](https://www.youtube.com/@FluxGarage).


## Watch the Demo and Getting Started Videos on Youtube

[![#1 - Smoothly Animated Robot Eyes on OLED Displays with the Robo Eyes Library](https://img.youtube.com/vi/ibSaDEkfUOI/0.jpg)](https://www.youtube.com/watch?v=ibSaDEkfUOI)
[![#2 - Getting Started With the Free Robo Eyes Arduino Library](https://img.youtube.com/vi/WtLWc5zzrmI/0.jpg)](https://www.youtube.com/watch?v=WtLWc5zzrmI)


## Installation

1. Open the Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries…**
3. Search for **"FluxGarage RoboEyes"**
4. Click **Install**

After installation, the example sketches can be found under  
**File → Examples → FluxGarage RoboEyes**.


## Functions

### General
- **begin()** _(screen-width, screen-height, max framerate)_
- **update()** _update eyes drawings in the main loop, limited by max framerate as defined in begin()_
- **drawEyes()** _same as update(), but without the framerate limitation_
- **setDisplayColors()** _(uint8_t background, uint8_t main)_
-> background: background and overlays, choose 0 for monochrome displays and 0x00 for grayscale displays such as SSD1322
-> main: drawings, choose 1 for monochrome displays and 0x0F for grayscale displays such as SSD1322 (0x0F = maximum brightness)

### Define Eye Shapes, all values in pixels
- **setWidth()** _(byte leftEye, byte rightEye)_
- **setHeight()** _(byte leftEye, byte rightEye)_
- **setBorderradius()** _(byte leftEye, byte rightEye)_
- **setSpacebetween()** _(int space) -> can also be negative_
- **setCyclops()** _(bool ON/OFF) -> if turned ON, robot has only one eye_

### Define Mood Expressions (Emotions)
- **setMood()** _mood expression, can be one of the following 21 moods_

| Mood | Expression | Eye Geometry & Animation |
|------|-----------|--------------------------|
| **DEFAULT** | neutral, centered | default rounded eyes |
| **TIRED** | heavy, droopy top lids | half-closed upper eyelids |
| **ANGRY** | furrowed eyebrows | angled top eyelids, squared borders |
| **HAPPY** | smiling, raised bottom lids | lifted bottom eyelids |
| **ALERT** | wide, raised brows | raised upper eyelids + taller eyes |
| **BORED** | half-closed, low energy | droopy eyelids, slow blink |
| **DESPAIR** | extreme sad | heavy inner eyelids **+ sweat drops**, slow blink |
| **DISORIENTED** | asymmetric, unsteady | asymmetric eye sizes + horizontal flicker |
| **EXCITED** | big, sparkling | larger round eyes + autoblinker |
| **FOCUSED** | narrowed, precise | narrowed eyes + squarish borders |
| **FURIOUS** | extreme anger | deep angry eyelids + horizontal flicker |
| **SAD** | droopy outer corners | sad eyelids + lowered position, slow blink |
| **SCARED** | wide, tense | raised "brows" + larger eyes + vertical flicker |
| **SLEEPY** | heavy eyelids, dozing | heavy lids + autoblinker, slow blink |
| **SURPRISED** | round, wide | maximally raised lids + very round eyes |
| **WORRIED** | furrowed inner brows | worried eyelids + slight narrowing |
| **ANNOYED** | half-closed asymmetric | asymmetric half-covered lids |
| **CONFUSED** | uneven, questioning look | asymmetric eyelid positions, tilted eyes |
| **CURIOUS** | tilted, attentive gaze | slight eye tilt + raised inner brows |
| **PROUD** | confident, slightly narrowed | raised chin posture + narrowed lower lids |
| **RELAXED** | soft, gentle expression | relaxed eyelids + slow relaxed blinking |

All geometry targets are reached with **fluid, frame-by-frame tweening** — when switching moods the eyes morph smoothly into the new expression instead of snapping.

Mood constants are easy to read, e.g.:
`roboEyes.setMood(SURPRISED);` or `roboEyes.setMood(WORRIED);`

### Define Gaze Direction (Look Up / Down / Left / Right / Diagonals)
- **setPosition()** _predefined positions, can be N, NE, E, SE, S, SW, W, NW, DEFAULT (default = horizontally and vertically centered)_
-> N = look up (north), E = look right (east), S = look down (south), W = look left (west), plus the four diagonal corners

Together with `setMood()`, `setPosition()` lets you combine any emotion with any gaze direction — e.g. a surprised expression while looking up, or a sleepy expression while looking down.

### Open / Close / Blink
- **open()** _open both eyes -> open(1,0) opens left eye only_
- **close()** _close both eyes -> close(1,0) closes left eye only_
- **blink()** _close and open both eyes_
- **blink(0,1)** _close and open right eye_
- **wink(left)** _wink with only one eye_

### Play Prebuilt Oneshot Animations
- **anim_confused()** _confused -> eyes shaking left and right_
- **anim_laugh()** _laughing -> eyes shaking up and down_

### Set Horizontal and/or Vertical Flicker
Alternately displaces the eyes in the defined amplitude in pixels:
- **setHFlicker()** _(bool ON/OFF, byte amplitude)_
- **setVFlicker()** _(bool ON/OFF, byte amplitude)_

### Animated Extras
- **setSweat()** _(bool ON/OFF) -> animated sweat drops in the upper screen area_

### Macro Animators
Blinks both eyes randomly:
- **setAutoblinker()** _(bool ON/OFF, int interval, int variation) -> turn on/off, set interval between each blink in full seconds, set range for additional random interval variation in full seconds_

Repositions both eyes randomly:
- **setIdleMode()** _(bool ON/OFF, int interval, int variation) -> turn on/off, set interval between each eye repositioning in full seconds, set range for additional random interval variation in full seconds_


## Example Sketches

Located in the **examples/** folder and also accessible via  
**File → Examples → FluxGarage RoboEyes** after installation:

- **i2c_SSD1306_Basics** _basic setup with autoblinker and idle animations_
- **spi_SSD1306_Basics** _basic setup for SPI connected displays_
- **spi_SSD1322_Basics** _basic setup for grayscale (4-bit) SSD1322 displays_
- **i2c_SH1106_Basics** _basic setup for SH1106 displays_
- **i2c_SSD1306_AnimationSequences** _how to build timed animation sequences_
- **i2c_SSD1306_ConfigurationBoard** _interactive configuration board with buttons and joystick_
- **i2c_SSD1306_SensorPlayground** _eyes reacting to sensors_
- **i2c_SSD1306_DHT22-TemperatureSensor** _eyes showing temperature moods_
- **spi_SSD1306_AnimationSequences** _timed animation sequences over SPI_
- **i2c_SSD1306_AllMoodsDemo** _cycles through all 21 mood expressions with smooth transitions (NEW)_
- **i2c_SSD1306_EmotionPositions** _combines emotions with gaze directions: look up, look down, look left, look right (NEW)_


## License

This library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.


## Further (Inofficial) Resources by Other Users
- micropython-roboeyes by mchobby: https://github.com/mchobby/micropython-roboeyes
- RoboEyes Micropython Edition by Youssef Tech: https://github.com/yousseftechdev/RoboEyes-Micropython
- RoboEyes for TFT displays by Youssef Tech: https://github.com/yousseftechdev/RoboEyesTFT
- MQTT control system by teletoby-swctv: https://github.com/teletoby-swctv/FluxGarage-RoboEyes-MQTT