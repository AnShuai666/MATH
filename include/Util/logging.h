/*
 * 日期:	2019-4-24
 * 时间:	17:01
 * 姓名:	安帅
 * @func    日志记录
*/

#ifndef MATH_LOGGING_H
#define MATH_LOGGING_H

#include <iostream>
#include "define.h"

UTIL_NAMESPACE_BEGIN
/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~日志记录类声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
class Logging
{
public:
    enum LogLevel
    {
        LOG_ERROR,
        LOG_WARNING,
        LOG_INFO,
        LOG_VERBOSE,
        LOG_DEBUG
    };

    struct NullStream:public std::ostream
    {
        NullStream(void):std::ostream(nullptr){}
        NullStream(NullStream const&) = delete;
        template <typename T>
        NullStream& operator << (T const& arg);
    };

public:
    Logging(void);
    Logging(LogLevel max_level);
    void set_max_level(LogLevel max_level);

    std::ostream& log(LogLevel logLevel) const;
    std::ostream& error(void) const;
    std::ostream& warning(void) const;
    std::ostream& info(void) const;
    std::ostream& verbose(void) const;
    std::ostream& debug(void) const;

private:
    LogLevel max_level;
    NullStream nullStream;
};

template <typename T>
inline Logging::NullStream&
Logging::NullStream::operator<<(const T &arg)
{
    return *this;
}

inline
Logging::Logging(void)
    :max_level(LOG_INFO)
{
}

inline
Logging::Logging(util::Logging::LogLevel max_level)
    :max_level(max_level)
{
}

inline void
Logging::set_max_level(util::Logging::LogLevel max_level)
{
    this->max_level = max_level;
}

inline std::ostream&
Logging::log(util::Logging::LogLevel logLevel) const
{
    if(logLevel > this->max_level)
        return const_cast<NullStream&>(this->nullStream);
    return (logLevel == LOG_ERROR) ? std::cerr:std::cout;
}

inline std::ostream&
Logging::error() const
{
    return this->log(LOG_ERROR);
}

inline std::ostream&
Logging::warning() const
{
    return this->log(LOG_WARNING);
}

inline std::ostream&
Logging::info() const
{
    return this->log(LOG_INFO);
}

inline std::ostream&
Logging::verbose() const
{
    return this->log(LOG_VERBOSE);
}

inline std::ostream&
Logging::debug() const
{
    return this->log(LOG_DEBUG);
}
UTIL_NAMESPACE_END
#endif //MATH_LOGGING_H
