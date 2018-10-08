#ifndef __fractal_creator_h__
#define __fractal_creator_h__

#include <string>
#include <cstdint>
#include "bitmap.hpp"
#include "mandelbrot.hpp"
#include "zoom.hpp"

class FractalCreator{
    int m_width{0};
    int m_height{0};
    uint32_t *m_histogram{nullptr};
    uint32_t *m_iterations{nullptr};
    Bitmap m_bitmap;
    ZoomList m_zoomList;
public:
    FractalCreator(int width, int height);
    ~FractalCreator();

    void add_zoom(const zoom &z);
    void doIterations();
    int writeimage_to_file(std::string filename);
};

#endif