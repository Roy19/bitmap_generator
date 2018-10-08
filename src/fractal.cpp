#include <cmath>
#include "fractal.hpp"

FractalCreator::FractalCreator(int width, int m_height):m_width(width), 
                                        m_height(m_height), m_bitmap(width, m_height), 
                                        m_zoomList(width, m_height){

    m_histogram = new uint32_t[Mandelbrot::MAX_ITERATIONS + 1] {0};
    m_iterations = new uint32_t[m_height*m_width] {0};
}

FractalCreator::~FractalCreator(){
    delete [] m_histogram;
    delete [] m_iterations;
}

int FractalCreator::writeimage_to_file(std::string filename){
    bool ret = m_bitmap.write_to_file(filename);
    if(ret == true)
        return 0;
    return 1;
}

void FractalCreator::add_zoom(const zoom &z){
    m_zoomList.add(z);
}

void FractalCreator::doIterations(){
    uint32_t total = 0; 

    for(int y = 0; y < m_height; y++){
        for(int x = 0; x < m_width; x++){
            std::pair<double, double> z = m_zoomList.doZoom(x,y);
            
            int iterations = Mandelbrot::getiterations(z.first, z.second);
            
            if (iterations != Mandelbrot::MAX_ITERATIONS){
                ++m_histogram[iterations];
                ++total;
                m_iterations[y*m_width + x] = iterations;
            }

        }
    }

    for(int y = 0;y < m_height;y++){
        for(int x = 0;x < m_width;x++){
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;
            double hue = 0.0;
            int iterations = m_iterations[y*m_width + x];

            if (iterations != Mandelbrot::MAX_ITERATIONS){
                for(int  i = 0;i < iterations;i++){
                    hue += (double)(m_histogram[i])/ total;
                }
                blue = pow(255,  hue);

                m_bitmap.set_pixel(x, y, red, green, blue);
            }
        }
    }
}