#include "request.h"

#include <iostream>
#include <string>
#include "response.h"
#include "typeheader.h"
#include "typeposts.h"
#include "typeblogpost.h"

const char *DELIM = "@>>>@";

Request::Request()
{}
Request::Request(const string &request)
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
                    return "Ill-formed header.";
                }
            } e(request);
            throw e;
        }
        string hdrStr(request.begin(), request.begin() + it);
        m_header.setMessage(request);

        m_message = string(request.begin() + it + 5, request.end());
    }
    catch (const std::exception &e)
    {
        Logger::Instance()->Log(Level::Err, "request", e.what());
        m_response.setBody(e.what());
    }
}

Response Request::GetResponse()
{
    auto type = TypeBase::Create(m_header.getType());
    string result = type->execute(m_header, m_message);   
    m_response.setBody(result);
    return m_response;
}
