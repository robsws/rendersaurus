#include "fragment_buffer.h"

#include <vector>

FragmentBuffer::FragmentBuffer(int width, int height) :
    width(width), height(height) {
    buffer = std::vector< std::vector<Fragment> >();
    for (int x = 0; x < width; ++x) {
        std::vector<Fragment> column = std::vector<Fragment>();
        std::vector<float> zColumn = std::vector<float>();
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
    buffer[x][y] = fragment;
}

void FragmentBuffer::clear() {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            set(x, y, Fragment());
            zBuffer[x][y] = 9999.0f;
        }
    }
}

void FragmentBuffer::blendFragments(const std::vector<Fragment>& fragments) {
    for (Fragment fragment : fragments) {
        auto depth = fragment.getDepth();
        auto position = fragment.getPosition();
        if(depth < zBuffer[position.x][position.y]) {
            set(position.x, position.y, fragment);
            zBuffer[position.x][position.y] = depth;
        }
    }
}