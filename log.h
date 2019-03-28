#ifndef LOG_H
#define LOG_H
#include <cstdarg>
#include <vector>
#include <string>

using std::string;
using std::vector;
enum Level
{
    Info = 0,
    Warn = 1,
    Err = 2
};
class app
{
    static app m_log;
    vector<string> m_logs;
    Level m_lvl;

  public:
    void setLevel(const Level &lvl)
    {
        m_lvl = lvl;
    }
    static app *logger()
    {
        return &m_log;
    }
    void log(Level lvl, const std::string &logMsg)
    {
        if (lvl >= m_lvl)
        {
            m_logs.push_back(logMsg);
        }
    }
    void log(Level lvl, char const *fmt, ...)
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
            log(lvl, std::string(temp));
            break;
        } while (0);
    }
    string toString()
    {
        string logs;
        for(auto log: m_logs)
        {
            logs.append(log);
            logs.append("\n");
        }
        return logs;
    }
};
#endif // LOG_H