#include "response.h"

    string Response::head(const string &title)
    {
        UNUSED(title);
        return "";
    }
    void Response::setTitle(const string &title)
    {
        m_title = title;
    }
    void Response::setBody(const string &body)
    {
        m_body = body;
    }
    string Response::toString()
    {
        return m_contentType + m_allowHeaders + m_cors + m_body;
    }