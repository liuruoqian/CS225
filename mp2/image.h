#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include "png.h"

using namespace std;

class Image : public PNG
{
public:
	//Why not declare constructor here?...already declared in PNG?
	//image();
	void flipleft();
	void adjustbrightness (int r, int g, int b);
	void invertcolors();

};


#endif
