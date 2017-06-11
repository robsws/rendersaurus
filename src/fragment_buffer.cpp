#include "fragment_buffer.h"

#include <vector>

using namespace std;

FragmentBuffer::FragmentBuffer(int width, int height) :
    width(width), height(height) {
    buffer = vector< vector<Fragment> >();
    for (int x = 0; x < width; ++x) {
        vector<Fragment> column = vector<Fragment>();
        for (int y = 0; y < height; ++y) {
            column.push_back(Fragment(0,0,0));
        }
        buffer.push_back(column);
    }
    
}

FragmentBuffer::~FragmentBuffer() {

}

float clamp(float value, float lower, float upper) {
    return max(lower, min(value, upper));
}

Fragment& FragmentBuffer::get(int x, int y) {
    // Clamp x and y to buffer size.
    x = clamp(x, 0, width);
    y = clamp(y, 0, height);
    // Fetch the colour from the buffer.
    return buffer[x][y];
}

void FragmentBuffer::set(int x, int y, const Fragment& fragment) {
    // Clamp x and y to buffer size.
    x = clamp(x, 0, width);
    y = clamp(y, 0, height);
    // Fetch colour
    Fragment& bufferFragment = this->get(x, y);
    // Set rgb values
    bufferFragment.set(fragment);
}