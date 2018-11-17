#include "bitmap.hpp"

Bitmap::Bitmap(uint32_t width, uint32_t height){
    /* Constructor for the Bitmap File Format.
     *
     * This constructor initializes the header,
     * info header and the default size of the
     * bitmap data which is stored as an array
     * of uint8_t (1 byte unsigned integer).
    */

    // set the header values
    this->header.fileSize = sizeof(bitmap_header) + sizeof(bitmap_info_header) +
                            width*height*3;
    this->header.dataOffset = sizeof(bitmap_header) + sizeof(bitmap_info_header);
    
    // set info header values
    this->info_header.width = width;
    this->info_header.height = height;

    // set the bitmap values
    this->m_width = width;
    this->m_height = height;
    this->m_pixels = new uint8_t[width * height * 3];

    memset(this->m_pixels, 0, width*height*3);
}

Bitmap::~Bitmap(){
    /* Destructor for the Bitmap class
     *
     * Frees the bitmap array allocated dynamically
    */
    this->m_width = 0;
    this->m_height = 0;
    delete [] m_pixels;
}

bool Bitmap::write_to_file(std::string filename){
    /* Writes the resulting bitmap to the specified
     * bitmap file including the main header and info
     * header 
    */
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary);

    if(!file){
        return false;
    }

    file.write(reinterpret_cast<char *>(&header), sizeof(bitmap_header));
    file.write(reinterpret_cast<char *>(&info_header), sizeof(bitmap_info_header));
    file.write(reinterpret_cast<char *>(m_pixels), m_width * m_height * 3);

    return true;
}

void Bitmap::set_pixel(int x[], int y, pixel p[]){
    /* Sets a particular pixel with coordinate (x,y)
     * in the bitmap.
     * 
     * x can be considered equivalent to the column number (staring from left).
     * y can be considered equivalent to the row number (starting from bottom).
     *            0 <= x <= width, 0 <= y <= height
     * 
     * The bitmap file is little endian, so the order of setting the memory is
     * like this
     *          pixel[0] -> blue
     *          pixel[1] -> green
     *          pixel[2] -> red
    */
   uint8_t* pixel_at_x_y;
   for(int i = 0;i < 4;i++){
       pixel_at_x_y = m_pixels + ((y*3)*m_width + (x[i]*3));  // as each pixel is 3 bytes long
       *pixel_at_x_y = p[i].b;
       *(pixel_at_x_y + 1) = p[i].g;
       *(pixel_at_x_y + 2) = p[i].r;
   }
}