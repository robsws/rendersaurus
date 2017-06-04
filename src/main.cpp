#include "../include/xterm_display.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
	if(argc != 3) {
		cout << "Usage: " << argv[0] << " <width> <height>" << endl;
		return EXIT_FAILURE;
	}
	
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);

	XtermDisplay* display = new XtermDisplay(width, height);
	display->initialise();
	for(int i = 0; i < 5000; ++i) {
		display->refresh();
	}
	display->finish();

	return EXIT_SUCCESS;
} 