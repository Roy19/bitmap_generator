#ifndef __mandelbrot_h__
#define __mandelbrot_h__

class Mandelbrot{
public:
    static const int MAX_ITERATIONS = 1000;
public:
    Mandelbrot();
    ~Mandelbrot();

    static int getiterations(double x, double y);
};

#endif