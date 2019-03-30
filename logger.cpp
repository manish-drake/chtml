#include "logger.h"
#include <ctime>
#include <sys/time.h>
#include <cstdio>
#include <cstdarg>
#include <memory>

Logger *Logger::s_logger = nullptr;

void Logger::Add(Logger *logger)
{
    this->m_loggers.push_back(logger);
}

Logger::~Logger()
{

}

void Logger::Log(const std::string &logMsg)
{
    for (auto &logger : m_loggers)
    {
        logger->Log(logMsg);
    }
}

void Logger::Log(Level level, const char *module, const std::string &logMsg)
{
    char buffer[1024];
    char tmBuff[32];
//    struct timeval tv;
    time_t now = time(nullptr);
    // time_t now;
    // gettimeofday(&tv, nullptr);
    // now = tv.tv_usec;
    tm * lclTime = localtime(&now);
    size_t sz = sprintf(tmBuff, "%d-%d %d:%d:%d", lclTime->tm_mon+1, lclTime->tm_mday, lclTime->tm_hour, lclTime->tm_min, lclTime->tm_sec);
    tmBuff[sz] = '\000';
    size_t nRet = sprintf(buffer, "%s:%0d [%s] %s", tmBuff, level, module, logMsg.c_str());
    std::string strLogMsg = {buffer, nRet};

    Log(strLogMsg);
}
void Logger::Log(Level level, char const *module, char const *fmt, ...)
{
    do
    {
        char temp[256];

        va_list args;
        va_start(args, fmt);
        const auto nRet = vsnprintf(temp, sizeof temp, fmt, args);
        va_end(args);

        if (nRet < 0)
            break;

        const size_t sz = nRet;
        if (sz < sizeof temp)
            temp[sz] = '\0';
        else
            temp[sizeof temp - 1] = '\0';
        Log(level, module, std::string(temp));
        break;
    } while (0);
}
