#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ncurses.h>

using namespace std;

int main(int argc, char **argv)
{
	int width = 256;
	int height = 224;

	initscr();
	if(has_colors() == FALSE) {
		endwin();
		printf("Terminal does not support colour...\n");
		return EXIT_SUCCESS;
	}
	start_color();
	
	WINDOW* win = newwin(height, width, 0, 0);		
	for(int i = 0; i < COLORS; i++) {
		init_pair(i+1, i, i);
	}
	for(int i = 0; i < 255; i++) {
		wattron(win, COLOR_PAIR(i));
		waddch(win, 'X');
		wattroff(win, COLOR_PAIR(i));
		wrefresh(win);
	}
	while(true) {}
	endwin();

	return EXIT_SUCCESS;
} 