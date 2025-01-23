/*
File:		LogManager.h
Author:		Keegan MacDonald
Created:	2025.01.19@00:53
Purpose:	Declare application logging functions for the Spectabilis Framework.
*/

#ifndef SPECTABILIS_LOGGING_H
#define SPECTABILIS_LOGGING_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

namespace Spectabilis {

#define SFLOG(SOURCE, LEVEL, ...) Application::Log(), \
	Application::Log().getDate(), Application::Log().getTime(), ": [", \
	#SOURCE, "] [", #LEVEL, "] ", __VA_ARGS__, "\n";

	// The singleton logging system manager class for Spectabilis Framework
	// applications.
	class LogManager {
	public:
		/*
		Disallow cloning of the LogManager class.
		Parameter: LogManager& - Unused parameter.
		*/
		LogManager(LogManager&) = delete;
		/*
		Disallow assignment of the LogManager class.
		Parameter: LogManager& - Unused parameter.
		*/
		void operator = (LogManager&) = delete;
		/*
		Get the singleton instance of the LogManager class.
		Returns: LogManager& - The singleton instance of the LogManager class.
		*/
		static LogManager& GetInstance();
		/*
		Initialize the logging system.
		Parameter: const std::vector<std::string>& logFileNames - The set of
		file names to write logs to.
		Returns: bool - Whether the logging system was initialized successfully.
		*/
		bool initialize(const std::vector<std::string>&);
		/*
		Write data to this log.
		Parameter: const T& data - The data to write.
		*/
		template <typename T>
		void write(const T& data) {
			std::cout << data;
			for (std::map<std::string, std::ofstream>::iterator it
				= m_logFiles.begin(); it != m_logFiles.end(); it++) {
				it->second << data;
			}
		}
		/*
		Free the logging system's memory.
		*/
		void destroy();
		/*
		Get the current system date as a string.
		Returns: std::string - The current date.
		*/
		std::string getDate() const;
		/*
		Get the current system time as a string.
		Returns: std::string - The current time.
		*/
		std::string getTime() const;
		/*
		Test whether the logging system has been initialized.
		Returns: bool - Whether the logging system has been initialized.
		*/
		bool isInitialized() const;
		/*
		Get the set of log file names.
		Returns: const std::vector<std::string> - The set of log file names.
		*/
		std::vector<std::string> getLogFileNames() const;
		/*
		Add a file name to the set of log file names.
		Parameter: const std::string& logFileName - The log file name to add.
		Returns: bool - Whether the log file name was added successfully.
		*/
		bool addLogFileName(const std::string&);
		/*
		Remove a file name from the set of log file names.
		Parameter: const std::string& logFileName- The log file name to remove.
		Returns: bool - Whether the log file name was removed successfully.
		*/
		bool removeLogFileName(const std::string&);

	private:
		// The singleton instance of the LogManager class.
		static LogManager Instance;
		// Whether the logging system has been initialized.
		bool m_initialized = false;
		// The set of files to write logs to.
		std::map<std::string, std::ofstream> m_logFiles;

		/*
		Construct an instance of the singleton LogManager class.
		*/
		LogManager();
	};

	/*
	Overload for the , operator on the LogManager class used to write any object
	to the logging system.
	Parameter: LogManager& logManager - The LogManager to write an object to.
	Parameter: const T& data - The data to write.
	Returns: LogManager& - The log manager written to, used to chain multiple
	objects together as a log.
	*/
	template <typename T>
	LogManager& operator , (LogManager& logManager, const T& data) {
		logManager.write(data);
		return logManager;
	}

}

#endif