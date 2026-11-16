#ifndef ROBOEYES_EXTENSIONS_H
#define ROBOEYES_EXTENSIONS_H

#include <Arduino.h>
#include "FluxGarage_RoboEyes.h"

template <typename Display>
class RoboEyesExtensions {

public:
    explicit RoboEyesExtensions(RoboEyes<Display>& eyes)
        : eyes_(eyes) {}

    // Register extension renderer
    void attach() {
        eyes_.setOverlayCallback(
            &RoboEyesExtensions::drawOverlay, this
        );
    }

    // Enable or disable low battery warning
    void setLowBattery(bool active) {
        lowBattery_ = active;
    }

private:
    RoboEyes<Display>& eyes_;
    bool lowBattery_ = false;

    static void drawOverlay(
        Display& display,
        int width,
        int height,
        void* context
    ) {
        (void)height;

        auto* self =
            static_cast<RoboEyesExtensions*>(context);

        // Blink every 500 ms
        if (!self->lowBattery_ ||
            (millis() % 1000UL) >= 500UL) {
            return;
        }

        const int x = width - 18;
        const int y = 2;

        // Battery outline (14x8)
        display.drawRect(x, y, 14, 8, 1);

        // Battery terminal
        display.fillRect(x + 14, y + 2, 2, 4, 1);

        // Low battery level
        display.fillRect(x + 2, y + 2, 2, 4, 1);
    }
};

#endif
