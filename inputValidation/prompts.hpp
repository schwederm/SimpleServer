#ifndef PROMPTS_HPP
#define PROMPTS_HPP

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <../server/server.hpp>
#include <windows.h> // For Sleep on Windows

bool getMessage(SOCKET& socket, std::string& message);
int promptNumPrimes(int& num, const SOCKET& socket);
std::string primePrompt(const int& index);
int promptGuess(int& guess, const int& randomPrime, const int& randomIndex, const SOCKET& socket);
int promptProceed(bool& proceed, const SOCKET& socket);

#endif