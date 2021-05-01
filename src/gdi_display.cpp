#include "gdi_display.h"
#include <windows.h>

using namespace std;

GdiDisplay::GdiDisplay(int width, int height, shared_ptr<FragmentBuffer> fragmentBufferPtr)
    : Display(width, height, fragmentBufferPtr) {
}

bool GdiDisplay::initialise() {
    hdc = GetDC(GetConsoleWindow());
    return true;
}

bool GdiDisplay::refresh() {
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            auto colour = fragmentBufferPtr->get(x,y);
            SetPixel(hdc, x, y, RGB(colour.red, colour.blue, colour.green));
        }
    }
    return true;
}

bool GdiDisplay::finish() {
    return true;
}