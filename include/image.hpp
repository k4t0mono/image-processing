#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>

#include "pixel.hpp"

/*
 * The basic struct to store the image's basic data;
 * Actally, it's just a class with all data public.
 */
struct Image {
	unsigned int height;
	unsigned int width;
	std::vector<Pixel> pixels;

	void load(char* filename);
	void save(char* filename);

	Pixel get_at(unsigned int x, unsigned int y);
	Pixel set_at(const Pixel& px, unsigned int x, unsigned int y);
};

#endif
