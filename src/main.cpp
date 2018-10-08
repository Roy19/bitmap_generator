#include "fractal.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char *argv[]){
    if (argc < 2){
        std::cout << "USAGE:" << argv[0] << " <file_name>.bmp" << std::endl;
        return -1;
    }
    std::string filename(argv[1]);

    FractalCreator fractal(WIDTH, HEIGHT);

    fractal.add_zoom(zoom(WIDTH/2, HEIGHT/2, 4.0 / WIDTH));
    fractal.add_zoom(zoom(295, HEIGHT- 202, 0.1));
    fractal.add_zoom(zoom(390, HEIGHT - 303, 0.1));

    fractal.add_range(0, RGB(0,0,0));
    fractal.add_range(200, RGB(41, 182, 246));
    fractal.add_range(500, RGB(132, 255, 255));
    fractal.add_range(Mandelbrot::MAX_ITERATIONS, RGB(255, 255, 255));

    fractal.doIterations();
    fractal.writeimage_to_file(filename);
    

    std::cout << "Finished" << std::endl;
    return 0;
}