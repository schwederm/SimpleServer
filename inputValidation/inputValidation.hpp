#ifndef INPUTVALIDATION_HPP
#define INPUTVALIDATION_HPP

#include <iostream>

void validateNumPrimes(int& num);
void primePrompt(const int& index);
void validateGuess(int& guess, const int& randomPrime, const int& randomIndex);
void validateProceed(bool& proceed);

#endif