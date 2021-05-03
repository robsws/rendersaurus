#pragma once

#include "fragment_buffer.h"
#include <memory>

using namespace std;

class Display {
    public:
        Display(int width, int height, shared_ptr<FragmentBuffer> fragmentBufferPtr)
            : width(width), height(height), fragmentBufferPtr(fragmentBufferPtr) {};
        virtual bool initialise() = 0; // Start up the display.
        virtual bool refresh() = 0; // Load the display with the contents of the fragment buffer.
        virtual bool finish() = 0; // Shut down the display.
        const int width;
        const int height;
        const shared_ptr<FragmentBuffer> fragmentBufferPtr;
    protected:
        bool initialised;
};