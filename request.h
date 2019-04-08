#ifndef REQUEST_H
#define REQUEST_H
#include <iostream>
#include <string>
#include "response.h"
#include "typeheader.h"
#include "typeposts.h"
#include "typeblogpost.h"

using std::cout;
using std::endl;

using std::string;

class Request
{
    string m_message;
    Header m_header;
    Response m_response;

  public:
    Request();
    Request(const string &request);
    Response GetResponse();
};

#endif //REQUEST_H