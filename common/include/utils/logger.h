//
// Created by Sathyam Vellal on 01/03/2018.
//

#ifndef CPP_BOOTSTRAP_LOGGER_H
#define CPP_BOOTSTRAP_LOGGER_H

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_VERBOSE
#endif

#include <sstream>
#include <boost/format.hpp>
#include <iostream>
#include <type_traits>

enum LogLevel {
    LOG_NOTHING,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG,
    LOG_VERBOSE
};

extern const char* LogLevelString[];

namespace Log {
    class FormattedLog {
    public:
        FormattedLog(LogLevel level, const wchar_t* msg)
                : fmt(msg), level(level) {}
        FormattedLog(const FormattedLog& fl)
                : fmt(fl.fmt), level(fl.level) {}
        FormattedLog operator=(const FormattedLog& fl) {
            return *this;
        }
        ~FormattedLog() {
            if (level <= LOG_LEVEL) {
                std::wcout << L"(" << LogLevelString[level] << L") " << fmt << std::endl;
            }
        }

        template <typename T>
        FormattedLog& operator%(T value) {
            fmt % value;
            return *this;
        }
    private:
        LogLevel level;
        boost::wformat fmt;
    };
};

template <LogLevel level>
Log::FormattedLog log(const wchar_t* msg) {
    return Log::FormattedLog(level, msg);
}

#endif //CPP_BOOTSTRAP_LOGGER_H
