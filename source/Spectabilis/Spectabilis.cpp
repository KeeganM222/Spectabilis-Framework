/*
File:		Spectabilis.cpp
Author:		Keegan MacDonld
Created:	2025.01.20@20:58
Purpose:	Implement the main application functions of the Spectabilis
			Framework.
*/

#include "Spectabilis.h"

namespace Spectabilis {

	// Implement Application Configuration class functions.

	Application::Configuration::Configuration() {
		// Generate the default log file name.
		std::string date = Application::Log().getDate();
		std::string time = Application::Log().getTime();
		std::string defaultLogFileName = date + "." + time.substr(1, 2) + "."
			+ time.substr(4, 2) + "." + time.substr(7, 2) + ".sflog";
		log.logFileNames = { defaultLogFileName, };
	}

	// Define Application class static variables.

	bool Application::Initialized = false;

	// Implement Application class functions.

	bool Application::Initialize(const Configuration& configuration) {
		if (Initialized) {
			return false;
		}
		// Initialize the logging system.
		if (!Log().initialize(configuration.log.logFileNames)) {
			return false;
		}
		Initialized = true;
		return true;
	}

	void Application::Destroy() {
		// Destroy the logging system.
		Log().destroy();
		Initialized = false;
	}

	LogManager& Application::Log() {
		return LogManager::GetInstance();
	}

	bool Application::IsInitialized() {
		return Initialized;
	}

	Application::Application() {

	}

}