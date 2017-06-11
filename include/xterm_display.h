#pragma once

#include <ncurses.h>

#include "display.h"

class XtermDisplay : public Display {
    public:
        XtermDisplay(int width, int height, FragmentBuffer* fragmentBuffer);
        bool initialise(); // Start up the display.
        bool refresh(); // Load the display with the contents of the fragment buffer.
        bool finish(); // Shut down the display.
    private:
        WINDOW* ncursesWindow;
};