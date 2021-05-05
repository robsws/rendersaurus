#include "display.h"

Display::Display(int width, int height)
    : width(width), height(height), fragmentBuffer(width, height) {}

int Display::getWidth() const {
    return width;
}

int Display::getHeight() const {
    return height;
}

void Display::clear() {
    fragmentBuffer.clear();
}

void Display::blend(const std::vector<Fragment>& fragments) {
    fragmentBuffer.blendFragments(fragments);
}