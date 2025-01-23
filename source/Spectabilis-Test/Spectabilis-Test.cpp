/*
File:		Spectabilis-Test.cpp
Author:		Keegan MacDonald
Created:	2025.01.19@00:55
Purpose:	Implement the main entry point of the test program for the
			Spectabilis Framework.
*/

#include <Spectabilis/Spectabilis.h>

#include <iostream>

using namespace Spectabilis;

// Implement Spectabilis-Test module functions.

/*
The main entry point of the Spectabilis-Test program.
Parameter: int argc - The number of command line arguments given to the program.
Parameter: char** argv - The command line arguments given to the program.
Returns: int - The exit code of the program (0 for success).
*/
int main(int argc, char** argv) {
	// Contruct a configuration for the Spectabilis Framework application.
	Application::Configuration configuration;
	// Initialize the application.
	if (!Application::Initialize(configuration)) {
		std::cout << "Failed to initialize application" << std::endl;
		return EXIT_FAILURE;
	}
	// Test the logging system macro.
	SFLOG(SPECTABILIS TEST, INFO, "Hello", " world", "!");
	// Destroy the application.
	Application::Destroy();
	return EXIT_SUCCESS;
}