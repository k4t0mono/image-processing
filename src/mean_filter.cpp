// Mean_filter

#include <iostream>
#include <vector>
#include <array>

#include "image.hpp"
#include "filters.hpp"
#include "kernel.hpp"


Kernel
gen_kernel(int m, int n)
{
	Kernel k(m, n);

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; ++j) {
			k[i][j] = Triple();
			k[i][j].x = i - (m - 1)/2;
			k[i][j].y = j - (n - 1)/2;
			k[i][j].factor = 1/(float)(m * n);
		}
	}

	return k;
}


Image
mean_filter(const Image& src, int level)
{
	int i = level * 2 + 1;
	return mean_filter(src, i, i);
}

Image
mean_filter(const Image& src, int mx, int my)
{
	if((mx % 2 == 0) || (my % 2 == 0))
		throw std::runtime_error("x and y of mean filter must be odd");

	Image mod = src;
	Kernel k = gen_kernel(mx, my);

	for(unsigned int x = 1; x < src.height-1; ++x) {
		for(unsigned int y = 1; y < src.width-1; ++y) {
			printf("(%d, %d): ", x, y);
			std::cout << "op: " << mod.get_at(x, y) << "\t";

			Pixel np;
			for(int i = 0; i < mx; i++) {
				for(int j = 0; j < my; j++) {
					//printf("k: (% 2d, % 2d, %.3f)\t", k.data[i][j].x,k.data[i][j].y,k.data[i][j].factor);
					int kx = k[i][j].x + x;
					int ky = k[i][j].y + y;
					float f = k[i][j].factor;

					//printf("px(%d, %d) = ", kx, ky);
					//std::cout << mod.get_at(kx, ky) << std::endl;

					Pixel op = mod.get_at(kx, ky);
					np.red += op.red * f;
					np.green += op.green * f;
					np.blue += op.blue * f;
					np.alpha = 0xff;
				}
			}

			std::cout << "np: " << np << std::endl;
			mod.set_at(np, x, y);
		}
	}

	return mod;
}
