#include <iostream>
#include <vector>

#include "lodepng.h"
#include "image.hpp"
#include "pixel.hpp"

/*
 * Load and decode the PNG file and store all data to the struct.
 */
void
Image::load(char* filename)
{
	std::vector<unsigned char> image;

	unsigned error;
	error = lodepng::decode(image, this->width, this->height, filename);
	if(error) {
		std::cerr << "decoder error " << error << ": "
			<< lodepng_error_text(error) << std::endl;
		exit(error);
	}

	for(unsigned int i = 0; i < this->height * this->width * 4; i += 4) {
		this->pixels.push_back(
			Pixel(image[i], image[i+1], image[i+2], image[1+3])
		);
	}
}

/*
 * Encode and write the PNG file from the struct.
 */
void
Image::save(char* filename)
{
	std::vector<unsigned char> png;

	for(auto it = this->pixels.begin(); it != this->pixels.end(); it++) {
		png.push_back((unsigned char) it->red);
		png.push_back((unsigned char) it->green);
		png.push_back((unsigned char) it->blue);
		png.push_back((unsigned char) it->alpha);
	}

	unsigned error;
	error = lodepng::encode(filename, png, this->width, this->height);
	if(error) {
		std::cerr << "encoder error " << error << ": "
			<< lodepng_error_text(error) << std::endl;
		exit(error);
	}
}

/*
 * Return the pixel at position (x, y).
 */
Pixel
Image::get_at(unsigned int x, unsigned int y)
{
	if(x >= this->width || y >= this->height) {
		std::cerr << "(" << x << ", " << y << ") " << this->width << "x" << this->height << std::endl;
		throw std::out_of_range("Invalid position for this image");
	}

	unsigned int i = x * this->width + y;

	return this->pixels[i];
}

/*
 * Set a new value for the pixel at (x, y) and return the old value.
 */
Pixel
Image::set_at(const Pixel& px, unsigned int x, unsigned int y)
{
	if(x >= this->width || y >= this->height) {
		std::cerr << "(" << x << ", " << y << ")" << std::endl;
		throw std::out_of_range("Invalid position for this image");
	}

	unsigned int i = x * this->width + y;
	Pixel p = this->pixels[i];
	this->pixels[i] = px;

	return p;
}
