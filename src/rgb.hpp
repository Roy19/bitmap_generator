#ifndef __rgb_h__
#define __rgb_h__

#include <cstdint>

typedef struct _rgb{
	uint8_t r{0};
	uint8_t g{0};
	uint8_t b{0};

	_rgb(uint8_t red, uint8_t green, uint8_t blue);
}RGB;

RGB operator-(RGB &first, RGB &second);

#endif