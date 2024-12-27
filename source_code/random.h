#ifndef RANDOM_H
#define RANDOM_H


#include <random>
#include <chrono>
using namespace std;


class RandomGenerator {

public:
    // Constructor initializes the random number generator
    RandomGenerator();
    // Method to generate a random float in the range [min, max]
    float Float(float , float );
    // Method to generate a random integer in the range [min, max]
    int Int(int , int ); 
	vector<vector<vector<float>>> generate3DVector(vector<int> dim , 
													int , int );
	

private:
    mt19937 mt; // Mersenne Twister engine
};

#endif
