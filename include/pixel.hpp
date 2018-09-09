#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <iostream>
#include <vector>

struct Pixel {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;

	Pixel();

	Pixel(unsigned char r, unsigned char g,
		unsigned char b, unsigned char a);

	Pixel& operator=(const Pixel& p);

	Pixel& operator+=(const Pixel& p);
	friend Pixel operator+(Pixel pa, const Pixel& pb);

	Pixel& operator-=(const Pixel& p);

	friend std::ostream& operator<<(std::ostream& os, const Pixel& px);
};

#endif
