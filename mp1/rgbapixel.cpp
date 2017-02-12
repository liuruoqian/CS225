#include "rgbapixel.h"

//RGBAPixel default constructor

RGBAPixel::RGBAPixel (){
	red = 255;
	green = 255;
	blue = 255;
	alpha = 255;
}

//RGBAPixel constructor with given r, g, b

RGBAPixel::RGBAPixel ( uint8_t r, uint8_t g, uint8_t b){
	red = r;
	green = g;
	blue = b;
	alpha = 255;
}
