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

int FractalCreator::get_range(int iteration){
    /* So all this function does is that for pixels which lead to a certain
     * no of iterations, it checks which range the iteration belongs to.
     * Then the pixel is assigned a color according to the color map given
     * by vector<RGB> colors[range].
    */
    int range = 0;
    for(int i = 0;i < m_ranges.size()-1; i++){
        if (iteration >= m_ranges[i] && iteration <= m_ranges[i+1]){
            range = i;
            break;
        }
    }
    return range;
}

void FractalCreator::add_range(int iteration, RGB rgb){
    m_ranges.push_back(iteration);
    m_colors.push_back(rgb);
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
            // get the iteration for that pixel pos
            int iterations = m_iterations[y*m_width + x];
            // find in which range does it belong to
            int range = get_range(iterations);
            int startIter = m_ranges[range];

            // it starts with the color at the beginning of the range
            RGB rgbStart = m_colors[range];
            // and ends with the color at the end of the range
            RGB rgbEnd = m_colors[range+1];
            // calculate the gradient form start to end color values
            RGB colorDiff = rgbEnd - rgbStart;
            double hue = 0.0;

            if (iterations != Mandelbrot::MAX_ITERATIONS){
                for(int  i = startIter;i < iterations;i++){
                    hue += (double)(m_histogram[i])/ total;
                }
                m_bitmap.set_pixel(x, y,rgbStart.r + colorDiff.r*hue,
                                    rgbStart.g + colorDiff.g*hue,
                                    rgbStart.b + colorDiff.b*hue);
            }
        }
    }
}