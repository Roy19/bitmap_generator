#include "fractal.hpp"

FractalCreator::FractalCreator(int width, int m_height):m_width(width), 
                                        m_height(m_height), 
                                        bmap(m_width, m_height){
}

int FractalCreator::writeimage_to_file(std::string filename){
    return bmap.write_to_file(filename);
}

void FractalCreator::iterations_sse2(){
    __m128 xscale = _mm_set_ps1((xlims[1]- xlims[0]) / m_width);
    __m128 yscale = _mm_set_ps1((ylims[1] - ylims[0]) / m_height);
    __m128 ONE = _mm_set_ps1(1);
    __m128 FOUR = _mm_set_ps1(4.0);
    __m128 TWO = _mm_set_ps1(2);
    __m128 xmin = _mm_set_ps1(xlims[0]);
    __m128 ymin = _mm_set_ps1(ylims[0]);
    int xcords[4];
    pixel p[4];

    #pragma omp parallel for schedule(dynamic, 1)
    for(int y = 0; y < m_height; y++){
        for(int x = 0; x < m_width; x += 4){
            __m128 cr = _mm_set_ps(x+3, x+2, x+1, x);
            __m128 ci = _mm_set_ps1(y);
            cr = _mm_add_ps(_mm_mul_ps(cr, xscale), xmin);
            ci = _mm_add_ps(_mm_mul_ps(ci, yscale), ymin);

            __m128 zr = _mm_set_ps1(0);
            __m128 zi = _mm_set_ps1(0);
            
            int iter = 0;
            __m128 iter_each = _mm_set_ps1(iter);
            while(++iter < MAX_ITERATIONS){
                __m128 zr1 = _mm_mul_ps(zr,zr);
                __m128 zi1 = _mm_mul_ps(zi,zi);
                __m128 zrzi = _mm_mul_ps(zr, zi);
                // zr = zr*zr - zi*zi + cr
                // zi = 2*zr*zi + ci
                zr = _mm_add_ps(_mm_sub_ps(zr1, zi1), cr);
                zi = _mm_add_ps(_mm_mul_ps(TWO, zrzi), ci);

                __m128 mag = _mm_add_ps(zr1, zi1);
                __m128 mask = _mm_cmplt_ps(mag, FOUR);
                // increment count only if |x+iy|*|x+iy| < 4
                iter_each = _mm_add_ps(_mm_and_ps(mask, ONE), iter_each);

                // if all |x+iy|*|x+iy| are greater than 4.0
                if(_mm_movemask_ps(mask) == 0)
                    break;
            }
            __m128i SRC = _mm_cvtps_epi32(iter_each);
            uint8_t* src = (uint8_t*)&SRC;
            for(int i = 0;i < 4;i++){
                xcords[i] = x+(i*3);
                p[i].r = src[i*4];
                p[i].g = src[i*4];
                p[i].b = src[i*4];
            }
            bmap.set_pixel(xcords, y, p);
        }
    }
}