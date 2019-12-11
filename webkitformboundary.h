#ifndef WEBKITFORMBOUNDARY_H
#define WEBKITFORMBOUNDARY_H
#include <string>
#include <exception>
#include <cstring>
#include <cstdio>
#include <regex>
#include <fstream>
#include <iostream>

using std::string;
class WebkitFormBoundary
{
private:
    bool m_valid;
    std::string m_sp;
    char* m_data;
    std::string m_filename;
    std::string m_name;
public:
    WebkitFormBoundary(char* data):m_valid(false), m_sp(data), m_data(data)
    {
        char* wfb = strstr(data, "------WebKitFormBoundary");
        if(wfb)
        {
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
    void Save(const std::string& path)
    {
        if(!m_valid)
        {
            throw std::bad_function_call();
        }
        size_t pos1 = m_sp.find("\r\n\r\n");
        size_t pos2 = m_sp.find("\r\n------WebKitFormBoundary");

        std::ofstream outfile;
        
        outfile.open(path, std::ios::binary | std::ios::out);
        outfile.write(&m_data[pos1 + 4], pos2-pos1-4);
        outfile.close();
    }

    ~WebkitFormBoundary() = default;
};
#endif //WEBKITFORMBOUNDARY_H