#include <iostream>
#include <vector>

#include "pixel.hpp"


Pixel::Pixel()
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;
	this->alpha = 0;
}

Pixel::Pixel(unsigned char r, unsigned char g,
			 unsigned char b, unsigned char a)
{
	this->red = r;
	this->green = g;
	this->blue = b;
	this->alpha = a;
}

Pixel&
Pixel::operator=(const Pixel& p)
{
	this->red = p.red;
	this->green = p.green;
	this->blue = p.blue;
	this->alpha = p.alpha;

	return *this;
}


std::ostream&
operator<<(std::ostream& os, const Pixel& px)
{
	os << std::hex << (int) px.red << (int) px.green << (int) px.blue
		<< (int) px.alpha << std::dec;
	return os;
}