#pragma once

#include "fragment_buffer.h"
#include <memory>

using namespace std;

class Display {
    public:
        Display(int width, int height);
        virtual ~Display() = default;
        virtual bool initialise() = 0; // Start up the display.
        virtual bool refresh() = 0; // Load the display with the contents of the fragment buffer.
        virtual bool finish() = 0; // Shut down the display.
        int getWidth() const;
        int getHeight() const;
        void clear();
        void blend(const std::vector<Fragment>& fragments);
    protected:
        bool initialised;
        const int width;
        const int height;
        FragmentBuffer fragmentBuffer;
};