#include "xterm_display.h"
#include "fragment_buffer.h"

#include <cstdlib>
#include <memory>

using namespace std;

XtermDisplay::XtermDisplay(int width, int height)
    : Display(width, height) {
}

bool XtermDisplay::initialise() {
    // Start up an ncurses window.
    initscr();
    if(has_colors() == FALSE) {
        endwin();
        return false;
    }
    start_color();
    ncursesWindow = newwin(height, width, 0, 0);
    // Initialise all 256 colors.
    // Pairs are initialised with both background and foreground as the same colour.
    for(int i = 0; i < COLORS; i++) {
        init_pair(i+1, i, i);
    }
    return true;
}

int getColourIndex(float colourComponent) {
    if (colourComponent < 47.5f) {
        return 0;
    }
    else if (colourComponent < 115.0f) {
        return 1;
    }
    else if (colourComponent < 155.0f) {
        return 2;
    }
    else if (colourComponent < 195.0f) {
        return 3;
    }
    else if (colourComponent < 235.0f) {
        return 4;
    }
    else {
        return 5;
    }
}

int convertRgbTo256(const Colour& colour) {
    int redIndex = getColourIndex(colour.getR());
    int greenIndex = getColourIndex(colour.getG());
    int blueIndex = getColourIndex(colour.getB());
    return 17 + redIndex*36 + greenIndex*6 + blueIndex;
}

bool XtermDisplay::refresh() {
    wmove(ncursesWindow,0,0);
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            Fragment fragment = fragmentBuffer.get(x, y);
            // Convert RGB colour to xterm 256 index
            int colour = convertRgbTo256(fragment);
            wattron(ncursesWindow, COLOR_PAIR(colour));
            waddch(ncursesWindow, 'X');
            wattroff(ncursesWindow, COLOR_PAIR(colour));
        }
    }
    wrefresh(ncursesWindow);
    return true;
}

bool XtermDisplay::finish() {
    endwin();
    return true;
}

