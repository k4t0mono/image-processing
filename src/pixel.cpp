#include <iostream>
#include <iomanip>
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
Pixel::operator+=(const Pixel& p)
{
	//std::cout << *this << " + " << p << " = ";
	this->red += p.red;
	this->green += p.green;
	this->blue += p.blue;
	this->alpha += p.alpha;

	//std::cout << *this << std::endl;
	return *this;
}

Pixel
operator+(Pixel pa, const Pixel& pb)
{
	pa += pb;
	return pa;
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
	using namespace std;

	os << setw(2) << setfill('0') << hex << (int) px.red  << dec;
	os << setw(2) << setfill('0') << hex << (int) px.green  << dec;
	os << setw(2) << setfill('0') << hex << (int) px.blue  << dec;
	os << setw(2) << setfill('0') << hex << (int) px.alpha  << dec;

	return os;
}
