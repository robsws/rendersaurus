#include "xterm_display.h"

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

	FragmentBuffer* fragmentBuffer = new FragmentBuffer(width, height);
	XtermDisplay* display = new XtermDisplay(width, height, fragmentBuffer);
	display->initialise();
	for(int i = 0; i < 2000; ++i) {
		for (int x = 0; x < width; ++x) {
			for (int y = 0; y < height; ++y) {
				Fragment fragment = Fragment((y+i)%256, 0, (x+i)%256);
				fragmentBuffer->set(x, y, fragment);
			}
		}
		display->refresh();
	}
	display->finish();
	
	delete fragmentBuffer;
	return EXIT_SUCCESS;
} 