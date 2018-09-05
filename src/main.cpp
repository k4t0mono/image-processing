#include <iostream>
#include <vector>

#include "image.hpp"


int main(int argc, char** argv)
{
	if(argc <= 1) {
		std::cout << "Usage:" << std::endl
			<< "./imgp <input> <output>" << std::endl;

		exit(1);
	}

	Image img;
	img.load(argv[1]);
	img.save(argv[2]);

	return 0;
}
