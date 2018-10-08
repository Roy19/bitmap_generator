#include "rgb.hpp"


RGB::_rgb(uint8_t red, uint8_t green, uint8_t blue){
	r = red;
	g = green;
	b = blue;
}

RGB operator-(RGB &first, RGB &second){
	return RGB(first.r-second.r, first.g - second.g,
				first.b - second.b);
}