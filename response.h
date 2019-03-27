#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>
#include "log.h"

using std::string;

#define UNUSED(x) (void)(x)
class Response
{
    const char *jsonTest = R"V0G0N(
{
   "name": "Manish Verma",
   "age": 45,
   "smoker": false
}
      )V0G0N";
    string m_contentType = "Content-type:application/json\r\n";
    string m_allowHeaders = "Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With\r\n";
    string m_cors = "Access-Control-Allow-Origin: *\r\n\r\n";
    string m_title = "Lean CGI Server";
    string m_body = "";
    string head(const string &title)
    {
        UNUSED(title);
        return "";
    }
    bool doAppendLogs = false;

  public:
    void setTitle(const string &title)
    {
        m_title = title;
    }
    void setBody(const string &body)
    {
        m_body = body;
    }
    string toString()
    {
        if (doAppendLogs)
        {
            return m_contentType + m_allowHeaders + m_cors + m_body + app::logger()->toString();
        }
        else
        {
            return m_contentType + m_allowHeaders + m_cors + m_body;
        }
    }
    void AppendLogs()
    {
        doAppendLogs = true;
    }
};

#endif //RESPONSE_H