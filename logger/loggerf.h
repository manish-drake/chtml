#ifndef LOGGERF_H
#define LOGGERF_H

#include "logger.h"
#include <fstream>
#include <exception>

class LoggerF : public Logger
{
  void Log(const std::string &logMsg) override
  {
    try
    {
      fprintf(m_fp, "%s\n", logMsg.c_str());
      fflush(m_fp);
    }
    catch (std::exception &e)
    {
      std::cout << e.what() << std::endl;
    }
  }
  FILE *m_fp;

public:
  LoggerF();
  LoggerF(const char *logHead);
  ~LoggerF();
};

#endif // LOGGERF_H
