#pragma once

#include "fragment.h"

#include <vector>

using namespace std;

class FragmentBuffer {
    public:
        FragmentBuffer(int width, int height);
        ~FragmentBuffer();
        Fragment get(int x, int y) const;
        void set(int x, int y, const Fragment& fragment);
        void blendFragments(const vector<Fragment>& fragments);
        void clear();
    private:
        // Buffer stores columns contiguously
        vector< vector<Fragment> > buffer;
        vector< vector<float> > zBuffer;
        const int width;
        const int height;
};