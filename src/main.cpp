#include <iostream>
#include <vector>

#include "lodepng.h"

using namespace std;


int main(int argc, char** argv)
{
	if(argc <= 1)
		std::cout << "Please enter PNG file name(s) to display" << std::endl;

	std::vector<unsigned char> image;
	unsigned width, height;

	unsigned error = lodepng::decode(image, width, height, argv[1]);
	if(error)
		std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	printf("%dx%d\n", width, height);
	for(int i = 0; i < 4; ++i) {
		printf("%02x", image[i]);
	}
	printf("\n");

	return 0;
}
