#include "fragment_buffer.h"

#include <vector>

using namespace std;

FragmentBuffer::FragmentBuffer(int width, int height) :
    _width(width), _height(height) {
    _buffer = vector<Fragment>();
    for (int i = 0; i < width * height; ++i) {
        _buffer.push_back(Fragment(0,0,0));
    }
}

FragmentBuffer::~FragmentBuffer() {

}

float clamp(float value, float lower, float upper) {
    return max(lower, min(value, upper));
}

Fragment& FragmentBuffer::get(int x, int y) {
    // Clamp x and y to buffer size.
    x = clamp(x, 0, _width);
    y = clamp(y, 0, _height);
    // Fetch the colour from the buffer.
    return _buffer[x*_height + y];
}

void FragmentBuffer::set(int x, int y, const Fragment& fragment) {
    // Clamp x and y to buffer size.
    x = clamp(x, 0, _width);
    y = clamp(y, 0, _height);
    // Fetch colour
    Fragment& bufferFragment = this->get(x, y);
    // Set rgb values
    bufferFragment.set(fragment);
}