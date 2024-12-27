#include "random.h"

RandomGenerator::RandomGenerator() 
{
	// Seed the random number generator with the current time
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	mt.seed(seed); // Mersenne Twister engine
}

// Method to generate a random float in the range [min, max]
float RandomGenerator::Float(float min, float max) 
{
	uniform_real_distribution<float> distribution(min, max);
	return distribution(mt);
}

// Method to generate a random integer in the range [min, max]
int RandomGenerator::Int(int min, int max) 
{
	uniform_int_distribution<int> distribution(min, max);
	return distribution(mt);
}
