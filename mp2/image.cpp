#include "image.h"
#include "png.h"

void Image::flipleft(){
	size_t wid = (*this).width();
	size_t hgt = (*this).height();
	// PNG Lifted(wid, hgt);

	if (wid % 2 == 0) {
		for (size_t i = 0 ; i < wid/2 ; i++){
			for (size_t j = 0; j < hgt; j++){
				RGBAPixel * ptr1, * ptr2;
				ptr1 = (*this)(i, j);
				ptr2 = (*this)(wid-i-1, j);
				RGBAPixel RGB = *ptr1;
				*ptr1 = *ptr2;
				*ptr2 = RGB;

			}
		}
	}
	else {
		for (size_t i = 0 ; i < (wid+1)/2 ; i++){
			for (size_t j = 0; j < hgt; j++){
				RGBAPixel * ptr1, * ptr2;
				ptr1 = (*this)(i, j);
				ptr2 = (*this)(wid-i-1, j);
				RGBAPixel RGB = *ptr1;
				*ptr1 = *ptr2;
				*ptr2 = RGB;
				
			}
		}

	}
}
void Image::adjustbrightness (int r, int g, int b){
	size_t wid = (*this).width();
	size_t hgt = (*this).height();

	for (size_t i = 0; i < wid; i++){
		for (size_t j = 0; j < hgt; j++){
			RGBAPixel * ptr;
			ptr = (*this)(i, j);
			
			if ((ptr->blue+b) > 255) ptr->blue = 255;
			else if ((ptr->blue+b) < 0) ptr->blue = 0;
                        else ptr->blue = ptr->blue + b;
			
			if ((ptr->red+r) > 255) ptr->red = 255;
			else if ((ptr->red+r) < 0) ptr->red = 0;
                        else ptr->red = ptr->red + r;
			
			if ((ptr->green+g) > 255) ptr->green = 255;
			else if ((ptr->green+g) < 0) ptr->green = 0;
                        else ptr->green = ptr->green + g;
		}
	}
}
void Image::invertcolors(){
	size_t wid = (*this).width();
	size_t hgt = (*this).height();

	for (size_t i = 0; i < wid; i++){
		for (size_t j = 0; j < hgt; j++){
			RGBAPixel * p;
			p = (*this)(i,j);
			p->red = 255 - p->red;
			p->green = 255 - p->green;
			p->blue = 255 - p->blue;

		}
	}
}
