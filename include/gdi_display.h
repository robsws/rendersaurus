#pragma once

#include "display.h"
#include <windows.h>
#include <memory>

using namespace std;

class GdiDisplay : public Display {
    public:
        GdiDisplay(int width, int height, shared_ptr<FragmentBuffer> fragmentBufferPtr);
        bool initialise(); // Start up the display.
        bool refresh(); // Load the display with the contents of the fragment buffer.
        bool finish(); // Shut down the display.
    private:
        HDC hdc;
};