//
// Created by Dawid Walenciak on 16/12/2020.
//

#ifndef VOICERECOGNITIONAI_LOGGER_H
#define VOICERECOGNITIONAI_LOGGER_H

#include <string>

namespace Utils {

class Logger {
public:
    template<typename T> static void info(T message);
    template<typename T> static void warning(T message);
    template<typename T> static void error(T message);
    template<typename T> static void debug(T message);

private:
    enum Severity{
        INFO,
        WARNING,
        ERROR,
        DEBUG
    };

    template<typename T>
    static void log(Severity severity, T message);

    static std::string severityToString(Severity severity);

};

}


#endif //VOICERECOGNITIONAI_LOGGER_H
