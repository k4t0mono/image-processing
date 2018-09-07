// filters

#ifndef FILTERS_HPP
#define FILTERS_HPP

#include "image.hpp"

struct Triple {
	int x;
	int y;
	float factor;
};

struct Kernel {
	int m;
	int n;
	float factor;
	Triple** data;
};

Image
mean_filter(const Image& src, int level);

Image
mean_filter(const Image& src, int x, int y);

#endif
