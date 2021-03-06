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
        switch (m_header.getType())
        {
        case TypeEnum::POSTS:
        {
            Logger::Instance()->Log(Level::Info, "request", "Executing Posts action");
            Posts posts;
            string result = posts.execute(m_header, m_message);
            m_response.setBody(result);
        }
        break;
        case TypeEnum::POST:
        {
            Logger::Instance()->Log(Level::Info, "request", "Executing Post action");
        }
        break;
        case TypeEnum::BLOGPOST:
        {
            Logger::Instance()->Log(Level::Info, "request", "Executing BlogPost action");
            BlogPost bPost;
            string result = bPost.execute(m_header, m_message);
            m_response.setBody(result);
        }
        break;
        case TypeEnum::BLOGCOMMENT:
        {
        }
        break;

        default:
            break;
        }

        return m_response;
}
