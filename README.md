# Bitmap Generator
This is a very simple and minimal program that outputs a bitmap image which draws a fractal.

## Building and running
Make a new directory called build (or anything). This project uses the
CMake build system. Then run the following:

```
$mkdir build && cd build
$cmake -DCMAKE_CXX_COMPILER=g++ \
        -DCMAKE_CXX_FLAGS=-O3 -Wall ..
$make
$./bitmap_gen <file_name>.bmp
```

Macros like ```CMAKE_CXX_COMPILER``` and ```CMAKE_CXX_FLAGS``` are optional. 

## ToDo Features
* Implement a colormap for different color schemes.
* Reorganize the ```main()```.
* Add other types of fractal algorithms.
* Add image filters.