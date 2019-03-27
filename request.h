#ifndef REQUEST_H
#define REQUEST_H
#include <iostream>
#include <string>
#include "response.h"
#include "typeheader.h"
#include "typeposts.h"

using std::cout;
using std::endl;

using std::string;

const char *DELIM = "@>>>@";

class Request
{
    string m_message;
    Header m_header;
    Response m_response;

  public:
    Request(const string &request)
    {
        try
        {
            auto it = request.find(DELIM);
            if (it > request.size())
            {
                struct excp : public std::exception
                {
                    string m_req;
                    excp(const string &req) : m_req{req}
                    {
                    }
                    const char *what() const noexcept override
                    {
                        return "Ill-formed header1.";
                    }
                } e(request);
                throw e;
            }
            string hdrStr(request.begin(), request.begin() + it);
            m_header.setMessage(request);

            m_message = string(request.begin() + it + 6, request.end());
        }
        catch (const std::exception &e)
        {
            m_response.setBody(e.what());
        }
    }

    Response GetResponse()
    {
        switch (m_header.getType())
        {
        case TypeEnum::POSTS:
        {
            Posts posts;
            string result = posts.execute(m_header.getAction(), m_message);
            m_response.setBody(result);
        }
        break;
        case TypeEnum::POST:
        {
        }
        break;

        default:
            break;
        }

        return m_response;
    }
};

#endif //REQUEST_H