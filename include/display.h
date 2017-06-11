#pragma once

#include "fragment_buffer.h"

class Display {
    public:
        Display(int width, int height, FragmentBuffer* fragmentBuffer) 
            : width(width), height(height), fragmentBuffer(fragmentBuffer) {};
        virtual bool initialise() = 0; // Start up the display.
        virtual bool refresh() = 0; // Load the display with the contents of the fragment buffer.
        virtual bool finish() = 0; // Shut down the display.
    protected:
        int width;
        int height;
        FragmentBuffer* fragmentBuffer;
};