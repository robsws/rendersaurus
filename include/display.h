#pragma once

#include "fragment_buffer.h"

class Display {
    public:
        Display(int width, int height, FragmentBuffer* fragmentBuffer) 
            : _width(width), _height(height), _fragmentBuffer(fragmentBuffer) {};
        virtual bool initialise() = 0; // Start up the display.
        virtual bool refresh() = 0; // Load the display with the contents of the fragment buffer.
        virtual bool finish() = 0; // Shut down the display.
    protected:
        int _width;
        int _height;
        FragmentBuffer* _fragmentBuffer;
};