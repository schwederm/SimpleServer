#include "prompts.hpp"

int promptNumPrimes(int& num, SOCKET socket)
{
    bool validInput = false;
	while (!validInput)
	{
		std::string message = "How many prime numbers do you want to generate?";
		bool success = sendMessage(socket, message.c_str()); // Send the message to the server
		if (!success)
		{
			std::cout << "Error sending message to server." << std::endl;
			return 1; // Return error code if sending failed
		}
		success = receiveMessage(socket, message); // Receive the response from the server
		if (!success)
		{
			std::cout << "Error receiving message from server." << std::endl;
			return 1; // Return error code if receiving failed
		}
		std::stringstream ss;
		if (ss.fail()) // Check if the input is valid
		{
			ss.clear(); // Clear the error flag
			ss.ignore(DEFAULT_BUF_LENGTH, '\n'); // Ignore the invalid input
			message = "Invalid input. Please enter a number.\n\n";
			success = sendMessage(socket, message.c_str()); // Send the error message to the server
			if (!success)
			{
				std::cout << "Error sending error message to server." << std::endl;
				return 1; // Return error code if sending failed
			}
		}
		else if (num < 1) // Check if the number is greater than 0
			std::cout << "Please enter a number greater than 0." << std::endl << std::endl;
		else
			validInput = true; // Input is valid, exit the loop
	}

	return 0; // Return 0 if the input is valid
}

std::string primePrompt(const int& index)
{
	std::string prompt = "What is the " + std::to_string(index);
    if (index >= 11 && index <= 13)
		prompt.append("th prime number?");
	else if (index % 10 == 1)
		prompt.append("st prime number? ");
	else if (index % 10 == 2)
		prompt.append("nd prime number? ");
	else if (index % 10 == 3)
		prompt.append("rd prime number? ");
	else
		prompt.append("th prime number? ");
	
	return prompt;
}

void promptGuess(int& guess, const int& randomPrime, const int& randomIndex)
{
    bool validInput = false;
	int numTries = 0; // Initialize the number of tries
	while (!validInput && numTries < 3)
	{
		std::string message = primePrompt(randomIndex); // Prompt the user to find the specific prime
		
		
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

void promptProceed(bool& proceed)
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