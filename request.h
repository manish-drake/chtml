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


class Request
{
    string m_message;
    Header m_header;
  public:
    Request(const string &request) 
    {
        try
        {
            auto it = request.find("@>>>@");
            if (it > request.size())
            {
                struct excp : public std::exception
                {
                    const char *what() const noexcept override
                    {
                        return "Ill-formed header.";
                    }
                } e;
                throw e;
            }
            string hdrStr(request.begin(), request.begin() + it);
            m_header.setMessage(request);
            

            m_message = string(request.begin() + it + 6, request.end());


            
        }
        catch (const std::exception &e)
        {
            Response resp;
            resp.setBody(e.what());
            cout << resp.toString();
        }
    }

    Response GetResponse()
    {
        Response response;
        if(m_header.getType() == "Posts")
        {
            Posts posts;
            string result = posts.execute(m_header.getAction(), m_message);
            response.setBody(result);
        }
        return response;
    }
};

#endif //REQUEST_H