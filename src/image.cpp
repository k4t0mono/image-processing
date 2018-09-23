#include <iostream>
#include <vector>
#include <png.h>

#include "image.hpp"
#include "pixel.hpp"

void
Image::load(char* filename)
{
	FILE *fp = fopen(filename, "rb");

	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png)
		abort();

	png_infop info = png_create_info_struct(png);
	if(!info)
		abort();

	if(setjmp(png_jmpbuf(png)))
		abort();

	png_init_io(png, fp);
	png_read_info(png, info);

	this->width = png_get_image_width(png, info);
	this->height = png_get_image_height(png, info);
	png_byte color_type = png_get_color_type(png, info);
	png_byte bit_depth = png_get_bit_depth(png, info);

	printf("size: %d x %d\n", this->width, this->height);
	printf("color type: %d\n", color_type);
	printf("bit depth: %d\n", bit_depth);

	if(bit_depth == 16)
		png_set_strip_16(png);

	if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png);

	if(png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png);

	if(color_type == PNG_COLOR_TYPE_RGB ||
			color_type == PNG_COLOR_TYPE_GRAY ||
			color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

	if(color_type == PNG_COLOR_TYPE_GRAY ||
			color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);

	png_read_update_info(png, info);

	this->row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
	for(int y = 0; y < height; y++)
		this->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));

	png_read_image(png, this->row_pointers);

	for(int y = 0; y < height; y++) {
		png_bytep row = this->row_pointers[y];

		for(int x = 0; x < width; x++) {
			png_bytep px = &(row[x * 4]);
			this->pixels.push_back(Pixel(px[0], px[1], px[2], px[3]));
		}

		free(this->row_pointers[y]);
	}
	free(this->row_pointers);

	fclose(fp);
}


void
Image::save(char* filename)
{
	FILE *fp = fopen(filename, "wb");

	if(!fp)
		abort();

	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png)
		abort();

	png_infop info = png_create_info_struct(png);
	if(!info)
		abort();

	if(setjmp(png_jmpbuf(png)))
		abort();

	png_init_io(png, fp);

	png_set_IHDR(
		png,
		info,
		this->width,
		this->height,
		8,
		PNG_COLOR_TYPE_RGBA,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
	);
	png_write_info(png, info);

	this->row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
	for(int y = 0; y < height; y++)
		this->row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));

	for(int y = 0; y < height; y++) {
		png_bytep row = this->row_pointers[y];

		for(int x = 0; x < width; x++) {
			png_bytep px = &(row[x * 4]);
			px[0] = this->get_at(x, y).red;
			px[1] = this->get_at(x, y).green;
			px[2] = this->get_at(x, y).blue;
			px[3] = this->get_at(x, y).green;
		}

	}

	png_write_image(png, row_pointers);
	png_write_end(png, NULL);

	fclose(fp);
}


Image::~Image()
{
	// TODO: Fazer o destrutor
	//for(int y = 0; y < this->height; y++)
		//free(this->row_pointers[y]);

	//free(this->row_pointers);
}


/*
 * Return the pixel at position (x, y).
 */
Pixel
Image::get_at(int x, int y)
{
	if(x >= this->width || y >= this->height) {
		std::cerr << "(" << x << ", " << y << ") " << this->width << "x" << this->height << std::endl;
		throw std::out_of_range("Invalid position for this image");
	}

	unsigned int i = y * this->width + x;

	return this->pixels[i];
}

/*
 * Set a new value for the pixel at (x, y) and return the old value.
 */
Pixel
Image::set_at(const Pixel& px, int x, int y)
{
	if(x >= this->width || y >= this->height) {
		std::cerr << "(" << x << ", " << y << ")" << std::endl;
		throw std::out_of_range("Invalid position for this image");
	}

	unsigned int i = y * this->width + x;
	Pixel p = this->pixels[i];
	this->pixels[i] = px;

	return p;
}

Image&
Image::operator+=(const Image& img)
{
	if((this->width != img.width) || (this->height != img.height))
		// TODO: Criar nova exception
		throw 4;

	for(unsigned int i = 0; i < this->height; i++) {
		for(unsigned int j = 0; j < this->width; j++) {
			int k = i * this->width + j;
			printf("(%2d, %2d) ", i, j);
			this->get_at(i, j) += img.pixels[k];
		}
	}

	return *this;
}

Image
operator+(Image a, const Image& b)
{
	a += b;
	return a;
}
