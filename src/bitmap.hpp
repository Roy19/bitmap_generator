#ifndef __bitmap_h__
#define __bitmap_h__

#include <fstream>
#include <iostream>
#include <cstdint>
#include <cstring>

#pragma pack(push, 2)

typedef struct _bitmap_header{
	char header[2]{'B','M'};		// contains 'BM'
	uint32_t fileSize;				// the file size of the bitmap file
	uint32_t reserved{0};				// reserved size
	uint32_t dataOffset;			// offset of the file where the data begins
}bitmap_header;

typedef struct _bitmap_info_header{
	uint32_t headerSize{40};			// info header size 
	uint32_t width;						// width of the image
	uint32_t height;					// height of the image
	uint16_t planes{1};					// no of planes
	uint16_t bitsPerPixel{24};			// per pixel we want 24 bits - 3 R, 3 G, 3 B
	uint32_t compression{0};			// no compression is allowed
	uint32_t dataSize{0};				// size of the actual data
	uint32_t horizontalRes{2400};		// horizontal resolution				
	uint32_t verticalRes{2400};			// vertical resolution
	uint32_t colors{0};					
	uint32_t importantColors{0};		
}bitmap_info_header;

#pragma pack(pop)

class Bitmap{
	bitmap_header header;
	bitmap_info_header info_header;
	uint32_t m_width{0};
	uint32_t m_height{0};
	uint8_t *m_pixels{nullptr};
public:
	Bitmap(uint32_t width, uint32_t height);	// constructor
	~Bitmap();									// destructor

	// utility functions
	bool write_to_file(std::string filename);
	void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);

	// getter functions
	bitmap_header get_header(){
		return this->header;
	}
	bitmap_info_header get_info_header(){
		return this->info_header;
	}
};

#endif
