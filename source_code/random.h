#include <random>
#include <chrono>

class RandomGenerator 
{
public:
    // Constructor initializes the random number generator
    RandomGenerator() {
        // Seed the random number generator with the current time
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        mt.seed(seed); // Mersenne Twister engine
    }

    // Method to generate a random float in the range [min, max]
    float Float(float min, float max) {
        std::uniform_real_distribution<float> distribution(min, max);
        return distribution(mt);
    }

    // Method to generate a random integer in the range [min, max]
    int Int(int min, int max) {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(mt);
    }

private:
    std::mt19937 mt; // Mersenne Twister engine
};


