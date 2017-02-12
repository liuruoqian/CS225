#include "png.h"

int main(){
	PNG OrigPNG = PNG("in.png"); 
	size_t wid = OrigPNG.width();
	size_t hgt = OrigPNG.height();
	PNG Rotated = PNG(wid, hgt);
	
	for (size_t i = 0; i < wid; i++){
		for (size_t j = 0; j < hgt; j++){
			RGBAPixel *ptr1, *ptr2;
			ptr1 = OrigPNG(i,j);
			ptr2 = Rotated(wid-i-1, hgt-j-1);
			ptr2->blue = ptr1->blue;
			ptr2->red = ptr1->red;
			ptr2->green = ptr1->green;
			ptr2->alpha = ptr1->alpha;

		}
	}

	Rotated.writeToFile("out.png");

	return 0;

}
