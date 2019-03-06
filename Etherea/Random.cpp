#include "Random.hpp"
#include <chrono>

using std::chrono::system_clock;

Random::Random() : rand(static_cast<unsigned int>(system_clock::now().time_since_epoch().count())) {}

Random::Random(unsigned int seed) : rand(seed) {}

void Random::seed(unsigned int seed)
{
	rand.seed(seed);
}

unsigned int Random::next()
{
	return rand();
}

unsigned int Random::next(unsigned int n)
{
	return next() % n;
}
