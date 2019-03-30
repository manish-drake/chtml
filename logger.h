#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

enum Level
{
    Info,
    Warn,
    Err
};
#define UNUSED(x) (void)(x)
class FileLogger;



class Logger
{
    static Logger *s_logger;
    static void setLoggers(Logger* sLogger)
    {
        sLogger->m_logMod =   getenv("LOG_MOD");
        const char* logLvl= getenv("LOG_LVL");
        if(logLvl)
            sLogger->m_logLvl = atoi(logLvl);
    }

    std::vector<Logger*> m_loggers;
    int m_logLvl;
    const char* m_logMod;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
protected:
    Logger()=default;
    ~Logger();
public:
    virtual void Log(const std::string &logMsg);
    static Logger *Instance()
    {
        if (!s_logger)
        {
            s_logger = new Logger;
            setLoggers(s_logger);
        }
        return s_logger;
    }
    void Add(Logger* logger);
    void Log(Level level, const char *module, const std::string &logMsg);
    void Log(Level level, char const *module, char const *fmt, ...);
};

#endif // LOGGER_H
