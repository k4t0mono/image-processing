// Kernel

#ifndef KERNEL_HPP
#define KERNELL_HPP

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

	Kernel(int m, int n);
	~Kernel();

	Triple* operator[](int i);
};

#endif
