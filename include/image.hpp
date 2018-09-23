#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <png.h>

#include "pixel.hpp"

/*
 * The basic struct to store the image's basic data;
 * Actally, it's just a class with all data public.
 */
struct Image {
	int height;
	int width;
	png_bytep *row_pointers;
	std::vector<Pixel> pixels;

	~Image();

	void load(char* filename);
	void save(char* filename);

	Pixel get_at(int x, int y);
	Pixel set_at(const Pixel& px, int x, int y);

	Image& operator+=(const Image& img);
	friend Image operator+(Image a, const Image& b);
};

#endif
