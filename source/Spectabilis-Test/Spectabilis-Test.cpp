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
	// Test the configuration structure memory.
	configuration.log.logFileNames.push_back("Test1.sflog");
	std::cout << "Configuration log file names:" << std::endl;
	for (size_t i = 0; i < configuration.log.logFileNames.size(); i++) {
		std::cout << "Log file name: \"" << configuration.log.logFileNames[i]
			<< "\"" << std::endl;
	}
	// Initialize the application.
	if (!Application::Initialize(configuration)) {
		std::cout << "Failed to initialize application" << std::endl;
		return EXIT_FAILURE;
	}
	// Test the application's IsInitialized function.
	if (Application::IsInitialized()) {
		std::cout << "Application is initialized" << std::endl;
	}
	// Test the logging system write function.
	Application::Log().write("Write function test\n");
	// Test the logging system's getDate and getTime functions.
	std::cout << "Date: " << Application::Log().getDate() << std::endl
		<< "Time: " << Application::Log().getTime() << std::endl;
	// Test the logging system's isInitialized function.
	std::cout << "Logging system initialized: "
		<< (int)Application::Log().isInitialized() << std::endl;
	// Test the logging system's getLogFileNames function.
	std::vector<std::string> logFileNames
		= Application::Log().getLogFileNames();
	for (size_t i = 0; i < logFileNames.size(); i++) {
		std::cout << "Log file name: \"" << logFileNames[i] << "\""
			<< std::endl;
	}
	// Test the logging system's addLogFileName and removeLogFileName functions.
	if (Application::Log().addLogFileName("Test2.sflog")) {
		std::cout << "Added log file name" << std::endl;
	}
	if (!Application::Log().addLogFileName("Test1.sflog")) {
		std::cout << "Failed to add duplicate log file" << std::endl;
	}
	if (Application::Log().removeLogFileName("Test1.sflog")) {
		std::cout << "Removed log file name" << std::endl;
	}
	if (!Application::Log().removeLogFileName("Non-existant.sflog")) {
		std::cout << "Failed to remove non-existant log file name" << std::endl;
	}
	std::cout << "Updated log file names:" << std::endl;
	logFileNames = Application::Log().getLogFileNames();
	for (size_t i = 0; i < logFileNames.size(); i++) {
		std::cout << "Log file name: \"" << logFileNames[i] << "\""
			<< std::endl;
	}
	// Test the logging system's , operator for calling write.
	Application::Log(), "Test 1234", "\n";
	// Test the logging system's main logging macro.
	SFLOG(SPECTABILIS TEST, INFO, "Hello", " world", "!");
	// Destroy the application.
	Application::Destroy();
	return EXIT_SUCCESS;
}