/*
File:		Spectabilis.h
Author:		Keegan MacDonald
Created:	2025.01.20@20:52
Purpose:	Declare the main application class of the Spectabilis Framework and
			supporting data structures.
*/

#ifndef SPECTABILIS_SPECTABILIS_H
#define SPECTABILIS_SPECTABILIS_H

#include "LogManager.h"

namespace Spectabilis {

	// The main application class of the Spectabilis Framework.
	class Application {
	public:
		// Configuration structure for Spectabilis Framework applications.
		class Configuration {
		public:
			// The configuration structure for the logging system.
			class Log {
			public:
				// The set of file names to write logs to.
				std::vector<std::string> logFileNames;
			} log;

			/*
			Construct a default application configuration structure.
			*/
			Configuration();
		};
		/*
		Disallow cloning of the Application class.
		Parameter: Application& - Unused parameter.
		*/
		Application(Application&) = delete;
		/*
		Disallow assignment of the Application class.
		Parameter: Application& - Unused parameter.
		*/
		void operator = (Application&) = delete;
		/*
		Initialize the Spectabilis application.
		Parameter: const Configuration& configuration - The configuration
		structure to initialize the application with.
		Returns: bool - Whether the application was initialized successfully.
		*/
		static bool Initialize(const Configuration&);
		/*
		Free the Spectabilis application's memory.
		*/
		static void Destroy();
		/*
		Get an instance of the application's logging system.
		Returns: LogManager& - The application's logging system.
		*/
		static LogManager& Log();
		/*
		Test whether the Spectabilis application has been initialized.
		Returns: bool - Whether the application has been initialized.
		*/

	private:
		// Whether the application has been initialized.
		static bool Initialized;

		/*
		Construct an instance of the singleton Application class.
		*/
		Application();
	};

}

#endif