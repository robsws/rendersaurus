#include "gdi_display.h"
#include <windows.h>

using namespace std;

GdiDisplay::GdiDisplay(int width, int height, int scale, shared_ptr<FragmentBuffer> fragmentBufferPtr)
    : Display(width, height, fragmentBufferPtr), scale(scale) {
}

bool GdiDisplay::initialise() {
    hdc = GetDC(GetConsoleWindow());
    mdc = CreateCompatibleDC(hdc);
    bitmap = CreateCompatibleBitmap(hdc, width*scale, height*scale);
    SelectObject(mdc, bitmap);
    return true;
}

bool GdiDisplay::refresh() {
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            auto colour = fragmentBufferPtr->get(x,y);
            drawPixel(x, y, colour);
        }
    }
    BitBlt(hdc, 0, 0, width*scale, height*scale, mdc, 0, 0, SRCCOPY);
    return true;
}

bool GdiDisplay::finish() {
    return true;
}

void GdiDisplay::drawPixel(int x, int y, Colour colour) {
    for (int x1 = x*scale; x1 < x*scale+scale; ++x1) {
        for (int y1 = y*scale; y1 < y*scale+scale; ++y1) {
            SetPixel(mdc, x1, y1, RGB(colour.red, colour.blue, colour.green));
        }
    }
}