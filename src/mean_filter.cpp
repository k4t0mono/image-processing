// Mean_filter

#include <iostream>
#include <vector>
#include <array>

#include "image.hpp"
#include "filters.hpp"


Kernel
gen_kernel(int m, int n)
{
	Kernel k;
	k.m = m;
	k.n = n;

	k.data = new Triple*[m];
	for(int i = 0; i < n; i++) {
		k.data[i] = new Triple[n];

		for(int j = 0; j < m; ++j) {
			k.data[i][j] = Triple();
			k.data[i][j].x = i - (m - 1)/2;
			k.data[i][j].y = j - (n - 1)/2;
			k.data[i][j].factor = 1/(float)(m * n);
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
	std::cout << k.data[0][0].x << std::endl;
	printf("%dx%d\n", mod.width, mod.height);

	int x = 1;
	int y = 8;
	std::cout << mod.get_at(x, y) << std::endl;

	Pixel np;
	for(int i = 0; i < mx; i++) {
		for(int j = 0; j < my; j++) {
			printf("k: (% 2d, % 2d, %.3f)\t", k.data[i][j].x,k.data[i][j].y,k.data[i][j].factor);
			int kx = k.data[i][j].x + x;
			int ky = k.data[i][j].y + y;
			float f = k.data[i][j].factor;

			printf("px(%d, %d) = ", kx, ky);
			std::cout << mod.get_at(kx, ky) << std::endl;

			Pixel op = mod.get_at(kx, ky);
			np.red += op.red * f;
			np.green += op.green * f;
			np.blue += op.blue * f;
			np.alpha = 0xff;
		}
	}

	std::cout << "np: " << np << std::endl;
	mod.set_at(np, x, y);

	return mod;
}