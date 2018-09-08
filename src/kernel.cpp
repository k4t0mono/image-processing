#include <iostream>

#include "kernel.hpp"

Kernel::Kernel(int m, int n)
{
	this->m = m;
	this->n = n;

	this->data = new Triple*[m];
	for(int i = 0; i < m; ++i) {
		this->data[i] = new Triple[n];
	}
}

Kernel::~Kernel()
{
	for(int i = 0; i < m; ++i) {
		delete[] this->data[i];
	}
	delete[] this->data;
}

Triple*
Kernel::operator[](int i) {
	if(i > m) {
		throw std::out_of_range("");
	}

	return this->data[i];
}
