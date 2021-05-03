#include "fragment_buffer.h"

#include <vector>

using namespace std;

FragmentBuffer::FragmentBuffer(int width, int height) :
    width(width), height(height) {
    buffer = vector< vector<Fragment> >();
    for (int x = 0; x < width; ++x) {
        vector<Fragment> column = vector<Fragment>();
        vector<float> zColumn = vector<float>();
        for (int y = 0; y < height; ++y) {
            column.push_back(Fragment());
            zColumn.push_back(9999.0f);
        }
        buffer.push_back(column);
        zBuffer.push_back(zColumn);
    }

}

FragmentBuffer::~FragmentBuffer() {

}

float clamp(float value, float lower, float upper) {
    return max(lower, min(value, upper));
}

Fragment FragmentBuffer::get(int x, int y) const {
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
    // Set rgb values
    buffer[x][y].set(fragment);
}

void FragmentBuffer::clear() {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            set(x, y, Fragment());
            zBuffer[x][y] = 9999.0f;
        }
    }
}

void FragmentBuffer::blendFragments(const vector<Fragment>& fragments) {
    for (Fragment fragment : fragments) {
        if(fragment.depth < zBuffer[fragment.position.x][fragment.position.y]) {
            set(fragment.position.x, fragment.position.y, fragment);
            zBuffer[fragment.position.x][fragment.position.y] = fragment.depth;
        }
    }
}