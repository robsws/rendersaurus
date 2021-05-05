#include "gdi_display.h"
#include <windows.h>

GdiDisplay::GdiDisplay(int width, int height, int scale)
    : Display(width, height), scale(scale) {
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
            auto colour = fragmentBuffer.get(x,y);
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
            SetPixelV(mdc, x1, y1, RGB(colour.getR(), colour.getB(), colour.getG()));
        }
    }
}