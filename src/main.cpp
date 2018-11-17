#include <time.h>
#include "fractal.hpp"

const int WIDTH = 1440;
const int HEIGHT = 1080;

int main(int argc, char *argv[]){
    if (argc < 2){
        std::cout << "USAGE:" << argv[0] << " <file_name>.bmp" << std::endl;
        return -1;
    }
    std::string filename(argv[1]);

    FractalCreator fractal(WIDTH, HEIGHT);
    
    clock_t start = clock();

    fractal.iterations_sse2();
    fractal.writeimage_to_file(filename);
    
    clock_t finish = clock();

    std::cout << "Finished in : " << (finish - start) / CLOCKS_PER_SEC << "secs" 
                        << std::endl;
    return 0;
}