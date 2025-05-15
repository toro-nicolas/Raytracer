/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** The Logs class implementation
*/
/**
 * @file Logs.cpp
 * @brief The Logs class implementation
 * @author Gianni TUERO, Lou PELLEGRINO, Nicolas TORO and Olivier POUECH
 */

#include "Logs.hpp"

namespace Lib::Logs {
    /**
     * @brief Get the local time
     * @return <b>std::string</b> The local time
     */
    std::string Logs::Time::getLocalTime()
    {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::ostringstream oss;

        oss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S")
            << "." << std::setfill('0') << std::setw(3) << ms.count();
        return oss.str();
    }

    /**
     * @brief Constructor of the Debug
     * @param file The file that contains the debug
     * @param line The line that contains the debug
     * @param func The function that contains the debug
     */
    Logs::Debug::Debug(const std::string file, const int line, const std::string func)
    {
        #ifdef DEBUG_MODE
        if (file.empty() && line == 0 && func.empty())
			std::cerr << RESET YELLOW;
		else
			std::cerr << RESET WHITE BOLD ITALIC
				"[" << Time::getLocalTime() << "] " <<
				"[FILE: " << file << ":" << line
				<< ", FUNCTION: " << func << "]: " RESET YELLOW << std::endl;
        #else
        (void)file;
        (void)line;
        (void)func;
        #endif
    }

    /**
     * @brief Destructor of the Debug
     */
    Logs::Debug::~Debug()
    {
        #ifdef DEBUG_MODE
        std::cerr << RESET << std::endl;
        #endif
    }

    /**
     * @brief Print a debug point
     * @param file The file that contains the debug point
     * @param line The line that contains the debug point
     * @param func The function that contains the debug point
     */
    void Logs::Debug::point(const std::string file, const int line, const std::string func)
    {
        #ifdef DEBUG_MODE
        std::cerr << RESET WHITE BOLD ITALIC
			"[" << Time::getLocalTime() << "] " <<
			"FILE: " << file << ":" << line <<
			RESET WHITE ", FUNCTION: " << func << RESET << std::endl;
        #else
        (void)file;
        (void)line;
        (void)func;
        #endif
    }

    /**
     * @brief Print a debug message
     * @param pf The message to print
     * @return <b>Debug &</b> The debug object
     */
    Logs::Debug& Logs::Debug::operator<<(std::ostream& (*pf)(std::ostream&))
    {
        #ifdef DEBUG_MODE
        std::cerr << pf;
        #else
        (void)pf;
        #endif
        return *this;
    }

    /**
     * @brief Constructor of the Error
     * @param file The file that contains the error
     * @param line The line that contains the error
     * @param func The function that contains the error
     */
    Logs::Error::Error(const std::string file, const int line, const std::string func)
    {
        if (file.empty() && line == 0 && func.empty())
            std::cerr << RESET RED;
        else
            std::cerr << RESET RESET WHITE BOLD ITALIC
                "[" << Time::getLocalTime() << "] " <<
                "[FILE: " << file << ":" << line
                << ", FUNCTION: " << func << "]: " RESET RED;
        std::cerr << std::endl;
    }

    /**
     * @brief Destructor of the Error
     */
    Logs::Error::~Error()
    {
        std::cerr << RESET << std::endl;
    }

    /**
     * @brief Print an error message
     * @param pf The message to print
     * @return <b>Error &</b> The error object
     */
    Logs::Error& Logs::Error::operator<<(std::ostream& (*pf)(std::ostream&))
    {
        std::cerr << pf;
        return *this;
    }

    /**
     * @brief Constructor of the Warning
     * @param file The file that contains the warning
     * @param line The line that contains the warning
     * @param func The function that contains the warning
     */
    Logs::Warning::Warning(const std::string file, const int line, const std::string func)
    {
        if (file.empty() && line == 0 && func.empty())
            std::cerr << RESET MAGENTA;
        else
            std::cerr << RESET WHITE BOLD ITALIC
                "[" << Time::getLocalTime() << "] " <<
                "[FILE: " << file << ":" << line
                << ", FUNCTION: " << func << "]: " RESET MAGENTA;
        std::cerr << std::endl;
    }

    /**
     * @brief Destructor of the Warning
     */
    Logs::Warning::~Warning()
    {
        std::cerr << RESET << std::endl;
    }

    /**
     * @brief Print a warning message
     * @param pf The message to print
     * @return <b>Warning &</b> The warning object
     */
    Logs::Warning& Logs::Warning::operator<<(std::ostream& (*pf)(std::ostream&))
    {
        std::cerr << pf;
        return *this;
    }

    /**
     * @brief Convert a string to a vector of strings
     * @param str The string to convert
     * @param delimiters The delimiters to use
     * @return <b>std::vector<std::string></b> The vector of strings
     */
    std::vector<std::string> stringToVector(std::string str, std::string delimiters)
    {
        std::vector<std::string> array;
        size_t start = str.find_first_not_of(delimiters);

        while (start != std::string::npos) {
            size_t end = str.find_first_of(delimiters, start);
            if (end == std::string::npos)
                end = str.size();
            array.push_back(str.substr(start, end - start));
            start = str.find_first_not_of(delimiters, end);
        }
        return array;
    }
}
