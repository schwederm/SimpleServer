#include <iostream>
#include "inputValidation.hpp"

void validateNumPrimes(int& num)
{
    bool validInput = false;
	while (!validInput)
	{
		std::cout << "How many prime numbers do you want to generate?  ";
		std::cin >> num;
		if (std::cin.fail()) // Check if the input is valid
		{
			std::cin.clear(); // Clear the error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
			std::cout << "Invalid input. Please enter a number." << std::endl << std::endl;
		}
		else if (num < 1) // Check if the number is greater than 0
			std::cout << "Please enter a number greater than 0." << std::endl << std::endl;
		else
			validInput = true; // Input is valid, exit the loop
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input in the buffer
}

void primePrompt(const int& index)
{
    if (index >= 11 && index <= 13)
		std::cout << "What is the " << index << "th prime number? ";
	else if (index % 10 == 1)
		std::cout << "What is the " << index << "st prime number? ";
	else if (index % 10 == 2)
		std::cout << "What is the " << index << "nd prime number? ";
	else if (index % 10 == 3)
		std::cout << "What is the " << index << "rd prime number? ";
	else
		std::cout << "What is the " << index << "th prime number? ";
}

void validateGuess(int& guess, const int& randomPrime, const int& randomIndex)
{
    bool validInput = false;
	int numTries = 0; // Initialize the number of tries
	while (!validInput && numTries < 3)
	{
		primePrompt(randomIndex); // Prompt the user to find the specific prime
		std::cin >> guess;
		if (std::cin.fail()) // Check if the input is valid
		{
			std::cin.clear(); // Clear the error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
			std::cout << "Invalid input. Please enter a number." << std::endl << std::endl;
		}
		else if (guess == randomPrime)
		{
			std::cout << "Correct!" << std::endl << std::endl;
			validInput = true;
		}
		else
		{
			numTries++; // Increment the number of tries
			if (numTries == 3)
				std::cout << "Incorrect. The correct answer is: " << randomPrime << std::endl << std::endl;
			else
				std::cout << "Incorrect. Try again." << std::endl;
		}
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining input in the buffer
}

void validateProceed(bool& proceed)
{
    bool validInput = false;
	while (!validInput)
	{
		char reply;
		std::cout << "Do you wish to continue? (y/n): ";
		std::cin >> reply;
		if (std::cin.fail()) // Check if the input is valid
		{
			std::cin.clear(); // Clear the error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
			std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl << std::endl;
		}
		else if (reply == 'y' || reply == 'Y')
		{
			proceed = true;
			validInput = true; // Input is valid, exit the loop
		}
		else if (reply == 'n' || reply == 'N')
		{
			proceed = false;
			validInput = true; // Input is valid, exit the loop
		}
		else
		{
			std::cin.clear(); // Clear the error flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
			std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl << std::endl;
		}
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining input in the buffer
}