#include <iostream>
#include <vector>

#include "image.hpp"
#include "filters.hpp"

int main(int argc, char** argv)
{
	if(argc <= 1) {
		std::cout << "Usage:" << std::endl
			<< "./imgp <input> <output>" << std::endl;

		exit(1);
	}

	Image a, b, c;
	a.load(argv[1]);
	b.load(argv[2]);

	c = a + b;
	c.save(argv[3]);

	//Image src;
	//src.load(argv[1]);

	//Image mod = mean_filter(src, 1);
	//mod.save(argv[2]);

	return 0;
}
