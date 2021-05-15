#include "loggerf.h"
#include <ctime>

LoggerF::LoggerF(): LoggerF("")
{

}
LoggerF::LoggerF(const char* logHead)
{
    time_t t = time(nullptr);
    tm *ltm = localtime(&t);
    char buffer[32];
    strftime(buffer, 32, "%Y%m%d%H.log", ltm);
    char logFile[255] = {0};
    sprintf(logFile, "./log/%s", buffer);
    
    m_fp = fopen(logFile, "a");
    this->Log({logHead});
}

LoggerF::~LoggerF()
{
    fclose(m_fp);
    delete m_fp;
}
