#ifndef PRIME_HPP
#define PRIME_HPP
// prime.hpp
// This header file defines the prime class, which generates a list of prime numbers

#include <iostream>
#include <math.h>
#include <random>
#include <vector>

class Prime
{
    public:
        Prime(int num)
        {
            std::cout << "Entering constructor. (debugging purposes)" << std::endl;
            primes = generatePrimes(num); // Generate the list of prime numbers
            randomIndex = generateRandomNum(primes.size()); // Generate a random index
            randomPrime = primes[randomIndex]; // Get the prime number at the random index
        }

        std::vector<int> getPrimes() const { return primes; }
        int getRandomIndex() const { return randomIndex; }
        int getRandomPrime() const { return randomPrime; }
    
    private:
        std::vector<int> primes;
        int randomIndex;
        int randomPrime;

        std::vector<int> generatePrimes(int num)
        {
            int size = (num < 6) ? 11 : (num * (log(num) + log(log(num))));
            std::vector<bool> isPrime(size + 1, true);
            isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime numbers
            for (int i = 2; i * i <= size; ++i)
            {
                if (isPrime[i])
                {
                    for (int j = i * i; j <= size; j += i)
                    {
                        isPrime[j] = false;
                    }
                }
            }

            int i = 0;
            int count = 0;
            std::vector<int> vec;
            while ((count < num) && (i <= size))
            {
                if (isPrime[i])
                {
                    vec.push_back(i);
                    count++;
                }
                i++;
            }

            return vec;
        }

        int generateRandomNum(int num)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, num - 1);
            return dis(gen); // Generate a random number between 0 and num-1
        }
};

std::ostream& operator<<(std::ostream& os, const Prime& prime)
{
    std::vector<int> primes = prime.getPrimes();
    int size = primes.size();
    os << "Generated Primes: ";
    for (int i = 0; i < size; ++i)
    {
        os << primes[i];
        if (i < size - 1) os << ", ";
    }

    return os;
}

#endif