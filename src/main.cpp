#include <cmath>
#include "bitmap.hpp"
#include "mandelbrot.hpp"
#include "zoom.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char *argv[]){
    if (argc < 2){
        std::cout << "USAGE:" << argv[0] << " <file_name>.bmp" << std::endl;
        return -1;
    }
    std::string filename(argv[1]);

    Bitmap bmap(WIDTH, HEIGHT);
    ZoomList zoomList(WIDTH, HEIGHT);

    zoomList.add(zoom(WIDTH/2, HEIGHT/2, 4.0 / WIDTH));
    zoomList.add(zoom(295, HEIGHT- 202, 0.1));
    zoomList.add(zoom(395, HEIGHT - 304, 0.1));
    
    uint32_t total = 0;
    uint32_t *histogram = new uint32_t[Mandelbrot::MAX_ITERATIONS] {0};
    uint32_t *iter = new uint32_t[WIDTH * HEIGHT] {0}; 

    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            std::pair<double, double> z = zoomList.doZoom(x,y);
            
            int iterations = Mandelbrot::getiterations(z.first, z.second);
            
            if (iterations != Mandelbrot::MAX_ITERATIONS){
                ++histogram[iterations];
                ++total;
                iter[y*WIDTH + x] = iterations;
            }

        }
    }

    //std::cout << "Total = " << total << std::endl;

    for(int y = 0;y < HEIGHT;y++){
        for(int x = 0;x < WIDTH;x++){
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;
            double hue = 0.0;
            int iterations = iter[y*WIDTH + x];

            if (iterations != Mandelbrot::MAX_ITERATIONS){
                for(int  i = 0;i < iterations;i++){
                    hue += (double)(histogram[i])/ total;
                }
                blue = pow(255,  hue);

                bmap.set_pixel(x, y, red, green, blue);
            }
        }
    }

    bmap.write_to_file(filename);

    delete [] histogram;
    delete [] iter;

    std::cout << "Finished" << std::endl;
    return 0;
}