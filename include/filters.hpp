// filters

#ifndef FILTERS_HPP
#define FILTERS_HPP

#include "image.hpp"

Image
mean_filter(const Image& src, int level);

Image
mean_filter(const Image& src, int x, int y);

#endif
