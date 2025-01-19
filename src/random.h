#ifndef RANDOM_H
#define RANDOM_H


#include <random>
#include <chrono>
using namespace std;


class RandomGenerator {

public:
    // Constructor initializes the random number generator
    RandomGenerator();
    // Method to generate a random double in the range [min, max]
    double Double(double , double );
    // Method to generate a random integer in the range [min, max]
    int Int(int , int ); 
	vector<vector<vector<double>>> generate3DVector(vector<int> dim , 
													int , int );
	

private:
    mt19937 mt; // Mersenne Twister engine
};

#endif
