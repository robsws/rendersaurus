#include "xterm_display.h"
#include "fragment_buffer.h"

#include <cstdlib>

XtermDisplay::XtermDisplay(int width, int height, FragmentBuffer* fragmentBuffer)
    : Display(width, height, fragmentBuffer) {
}

bool XtermDisplay::initialise() {
    // Start up an ncurses window.
    initscr();
	if(has_colors() == FALSE) {
		endwin();
		return false;
	}
	start_color();
	_ncurses_window = newwin(_height, _width, 0, 0);	
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

int convertRGBto256(const Colour& colour) {
    int redIndex = getColourIndex(colour.red());
    int greenIndex = getColourIndex(colour.green());
    int blueIndex = getColourIndex(colour.blue());
    return 17 + redIndex*36 + greenIndex*6 + blueIndex;
}

bool XtermDisplay::refresh() {
    wmove(_ncurses_window,0,0);
    for(int x = 0; x < _width; ++x) {
        for(int y = 0; y < _height; ++y) {
            Fragment fragment = _fragmentBuffer->get(x, y);
            // Convert RGB colour to xterm 256 index
            int colour = convertRGBto256(fragment);
            wattron(_ncurses_window, COLOR_PAIR(colour));
            waddch(_ncurses_window, 'X');
            wattroff(_ncurses_window, COLOR_PAIR(colour));
        }
	}
    wrefresh(_ncurses_window);
    return true;
}

bool XtermDisplay::finish() {
    endwin();
    return true;
}

