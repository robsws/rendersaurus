#pragma once

#include "fragment.h"

#include <vector>

using namespace std;

class FragmentBuffer {
    public:
        FragmentBuffer(int width, int height);
        ~FragmentBuffer();
        Fragment& get(int x, int y);
        void set(int x, int y, const Fragment& fragment);
    private:
        // Buffer stores columns contiguously
        vector<Fragment> _buffer;
        int _width;
        int _height;
};