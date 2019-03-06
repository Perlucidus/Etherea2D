#pragma once

#include <random>

class Random {
public:
	Random();
	Random(unsigned int seed);

	void seed(unsigned int seed);
	unsigned int next();
	unsigned int next(unsigned int n);
private:
	std::minstd_rand rand;
};
