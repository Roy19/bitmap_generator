#include <complex>
#include "mandelbrot.hpp"

Mandelbrot::Mandelbrot(){
}

Mandelbrot::~Mandelbrot(){
}

int Mandelbrot::getiterations(double x, double y){
    int iterations = 0;
    std::complex<double> z = 0;
    std::complex<double> c(x,y);

    while(abs(z) < 2 and iterations < MAX_ITERATIONS){
        z = z*z + c;
        ++iterations;
    }
    
    return iterations;
}