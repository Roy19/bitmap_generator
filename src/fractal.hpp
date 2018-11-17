#ifndef __fractal_creator_h__
#define __fractal_creator_h__

#include <string>
#include <vector>
#include <cstdio>
#include <cstdint>
#include <xmmintrin.h>
#include "bitmap.hpp"
#include "mandelbrot.hpp"

class FractalCreator{
    int m_width{0};
    int m_height{0};
    Bitmap bmap;
public:
    FractalCreator(int width, int height);

    void iterations_sse2();
    int writeimage_to_file(std::string filename);
};

#endif