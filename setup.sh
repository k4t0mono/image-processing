#!/usr/bin/bash

mkdir obj lib

curl "https://raw.githubusercontent.com/lvandeve/lodepng/master/lodepng.cpp" \
	-o "./lib/lodepng.cpp";

$CC -Iinclude -c ./lib/lodepng.cpp -o ./lib/lodepng.o;

ar rcs ./lib/liblodepng.a ./lib/lodepng.o

rm ./lib/lodepng*


echo "done :3"

exit
