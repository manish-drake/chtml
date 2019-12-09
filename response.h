#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>
#include "logger.h"

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
    string head(const string &title);

  public:
    void setTitle(const string &title);
    void setBody(const string &body);
    string toString();
};

#endif //RESPONSE_H