//
// Created by Dawid Walenciak on 16/12/2020.
//

#include "Logger.h"

#include <sstream>
#include <iostream>

namespace Utils {

template<typename T>
void Logger::info(T message) {
    log(INFO, message);
}

template<typename T>
void Logger::warning(T message) {
    log(WARNING, message);
}

template<typename T>
void Logger::error(T message) {
    log(ERROR, message);
}

template<typename T>
void Logger::debug(T message) {
    log(DEBUG, message);
}

template<typename T>
void Logger::log(Logger::Severity severity, T message) {
    std::stringstream stream;
    stream << "[" + severityToString(severity) + "] " << message;

    std::cout << stream.str() << std::endl;
}

std::string Logger::severityToString(Logger::Severity severity) {
    switch (severity) {
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        default:
            return "DEBUG";
    }
}

template void Logger::info(const std::string& message);
template void Logger::info(std::string message);
template void Logger::info(const char* message);
template void Logger::info(int message);
template void Logger::info(float message);
template void Logger::info(double message);
template void Logger::info(char message);

template void Logger::warning(const std::string& message);
template void Logger::warning(std::string message);
template void Logger::warning(const char* message);
template void Logger::warning(int message);
template void Logger::warning(float message);
template void Logger::warning(double message);
template void Logger::warning(char message);

template void Logger::error(const std::string& message);
template void Logger::error(std::string message);
template void Logger::error(const char* message);
template void Logger::error(int message);
template void Logger::error(float message);
template void Logger::error(double message);
template void Logger::error(char message);

template void Logger::debug(const std::string& message);
template void Logger::debug(std::string message);
template void Logger::debug(const char* message);
template void Logger::debug(int message);
template void Logger::debug(float message);
template void Logger::debug(double message);
template void Logger::debug(char message);

template void Logger::log(Logger::Severity severity, const std::string& message);
template void Logger::log(Logger::Severity severity, std::string message);
template void Logger::log(Logger::Severity severity, const char* message);
template void Logger::log(Logger::Severity severity, int message);
template void Logger::log(Logger::Severity severity, float message);
template void Logger::log(Logger::Severity severity, double message);
template void Logger::log(Logger::Severity severity, char message);

}
