#pragma once

#include "display.h"
#include "colour.h"
#include <windows.h>
#include <memory>

class GdiDisplay : public Display {
    public:
        GdiDisplay(int width, int height, int scale);
        bool initialise(); // Start up the display.
        bool refresh(); // Load the display with the contents of the fragment buffer.
        bool finish(); // Shut down the display.
    private:
        HDC hdc; // hardware
        HDC mdc; // buffer
        HBITMAP bitmap;
        int scale;
        void drawPixel(int x, int y, Colour colour);
};