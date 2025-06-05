#include "prime.hpp"

int main()
{
    std::cout << "Starting the Prime Number Generator..." << std::endl;
    int num = 100;             // Default number of primes to generate
    std::cout << "Entering constructor. (debugging purposes)" << std::endl;
    Prime primeGenerator(num); // Create a Prime object to generate primes
    std::cout << "Exiting constructor. (debugging purposes)" << std::endl;
    
    int randomIndex = primeGenerator.getRandomIndex();    // Get the random index
    int randomPrime = primeGenerator.getRandomPrime();    // Get the random prime

    std::cout << primeGenerator << std::endl; // Print the list of primes
    std::cout << "Random Index: " << randomIndex << ", Random Prime: " << randomPrime << std::endl;

    return 0;
}