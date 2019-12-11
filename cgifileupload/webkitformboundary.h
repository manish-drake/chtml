#ifndef WEBKITFORMBOUNDARY_H
#define WEBKITFORMBOUNDARY_H
#include <string>
#include <exception>
#include <cstring>
#include <cstdio>
#include <regex>
#include <iostream>

using std::string;
class WebkitFormBoundary
{
private:
    bool m_valid;
    std::string m_sp;
    char* m_data;
    std::string m_wfb;
    std::string m_filename;
    std::string m_name;
public:
    WebkitFormBoundary(std::string data):m_valid(false), m_sp(data)
    {
        std::regex rxWFB(R"###((------WebKitFormBoundary.*)\r\n?)###");
        std::smatch mWFB;
        if(std::regex_search(m_sp, mWFB, rxWFB))
        {
            m_wfb = mWFB.str(1);

            m_valid = true;

            std::regex rxName(R"###(name="(.*)";)###"), rxFilename(R"###(filename="(.*)")###");
            std::smatch mName, mFilename, mDlim;

            if(std::regex_search(m_sp, mName, rxName))
            {
                m_name = mName.str(1);
            }

            if(std::regex_search(m_sp, mFilename, rxFilename))
            {
                m_filename = mFilename.str(1);
            }
        }
    }
    bool IsValid()
    {
        return m_valid;
    }

    std::string GetName()
    {
        return m_name;
    }
    std::string GetFilename()
    {
        return m_filename;
    }
    ~WebkitFormBoundary() = default;
};
#endif //WEBKITFORMBOUNDARY_H