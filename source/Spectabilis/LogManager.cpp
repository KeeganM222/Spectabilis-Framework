/*
File:		LogManager.cpp
Author:		Keegan MacDonald
Created:	2025.01.19@00:54
Purpose:	Implement application logging functions for the Spectabilis
			Framework.
*/

#include "Spectabilis.h"

#include <sstream>
#include <iomanip>
#include <iostream>

namespace Spectabilis {

	// Define LogManager class static variables.

	LogManager LogManager::Instance;

	// Implement LogManager class functions.

	LogManager& LogManager::GetInstance() {
		return LogManager::Instance;
	}

	bool LogManager::initialize(const std::vector<std::string>& logFileNames) {
		if (m_initialized) {
			return false;
		}
		// Open each of the initial log file names.
		for (size_t i = 0; i < logFileNames.size(); i++) {
			if (!addLogFileName(logFileNames[i])) {
				return false;
			}
		}
		m_initialized = true;
		return true;
	}

	void LogManager::destroy() {
		// Close each of the log file names.
		std::vector<std::string> logFileNames = getLogFileNames();
		for (size_t i = 0; i < logFileNames.size(); i++) {
			removeLogFileName(logFileNames[i]);
		}
		m_initialized = false;
	}

	std::string LogManager::getDate() const {
		// Get the current date and format it YYYY.MM.DD.
		std::time_t timeBuffer = std::time(0);
		std::tm* currentTime = std::localtime(&timeBuffer);
		std::ostringstream oss;
		oss << std::setfill('0')
			<< std::setw(4) << (1900 + currentTime->tm_year) << "."
			<< std::setw(2) << (1 + currentTime->tm_mon) << "."
			<< std::setw(2) << (currentTime->tm_mday);
		return oss.str();
	}

	std::string LogManager::getTime() const {
		// Get the current time and format it @HH:MM:SS.
		std::time_t timeBuffer = std::time(0);
		std::tm* currentTime = std::localtime(&timeBuffer);
		std::ostringstream oss;
		oss << std::setfill('0') << "@"
			<< std::setw(2) << (currentTime->tm_hour) << ":"
			<< std::setw(2) << (currentTime->tm_min) << ":"
			<< std::setw(2) << (currentTime->tm_sec);
		return oss.str();
	}

	bool LogManager::isInitialized() const {
		return m_initialized;
	}

	std::vector<std::string> LogManager::getLogFileNames() const {
		// Get all the key values of the log files map.
		std::vector<std::string> logFileNames;
		for (std::map<std::string, std::ofstream>::const_iterator it
			= m_logFiles.begin(); it != m_logFiles.end(); it++) {
			logFileNames.push_back(it->first);
		}
		return logFileNames;
	}

	bool LogManager::addLogFileName(const std::string& logFileName) {
		// Check that the log file name is not already open.
		std::map<std::string, std::ofstream>::iterator it
			= m_logFiles.find(logFileName);
		if (it != m_logFiles.end()) {
			return false;
		}
		// Add the log file name and open an output stream to it.
		m_logFiles[logFileName] = std::ofstream();
		m_logFiles[logFileName].open(logFileName);
		// Test the log file output stream.
		if (!m_logFiles[logFileName].good()) {
			return false;
		}
		return true;
	}

	bool LogManager::removeLogFileName(const std::string& logFileName) {
		// Check that the log file name is in the map.
		std::map<std::string, std::ofstream>::iterator it
			= m_logFiles.find(logFileName);
		if (it == m_logFiles.end()) {
			return false;
		}
		// Close the log file output stream and remove it from the map.
		it->second.close();
		m_logFiles.erase(it);
		return true;
	}

	LogManager::LogManager() {

	}

}