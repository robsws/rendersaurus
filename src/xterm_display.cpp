#include "../include/xterm_display.h"
#include "../include/fragment_buffer.h"

#include <cstdlib>

XtermDisplay::XtermDisplay(int width, int height) : Display(width, height) {
    _fragmentBuffer = new FragmentBuffer(width, height);
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

bool XtermDisplay::refresh() {
    // For now, ignore fragment buffer.
    // Just output a block colour to screen.
    int colour = rand() % 256;
    wmove(_ncurses_window,0,0);
    for(int i = 0; i < _width * _height; i++) {
		wattron(_ncurses_window, COLOR_PAIR(colour));
		waddch(_ncurses_window, 'X');
		wattroff(_ncurses_window, COLOR_PAIR(colour));
	}
    wrefresh(_ncurses_window);
    return true;
}

bool XtermDisplay::finish() {
    endwin();
    return true;
}