#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include "typeheader.h"
#include "response.h"
#include "request.h"
#include "logger.h"
#include "loggerc.h"
#include "loggerf.h"
#include <cstring>


using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::ostringstream;
using std::string;


#define UNUSED(x) (void)(x)



static string readRequest()
{
    const char *lenStr = getenv("CONTENT_LENGTH");
    int len = -1;
    Logger::Instance()->Log(Level::Info, "main", "Content length: %s", lenStr);
    if (lenStr && (len = atoi(lenStr)) != 0)
    {
        Logger::Instance()->Log(Level::Info, "main", "Content length: %i", len);
        char buffer[len] = {0};
        char postData[len] = {0};
        while (fgets(buffer, len, stdin))
        {
            strcat(postData, buffer);
        }
        Logger::Instance()->Log(Level::Info, "main", "request: %s", postData);
        return postData;
    }
    else
    {
        return "";
    }
}

static string readDRequest()
{
    string request;
    ifstream fpost("post.json");
    ostringstream strm;
    strm << fpost.rdbuf();
    request = strm.str();
    fpost.close();
    return request;
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    Logger::Instance()->Add(new LoggerF);
    Logger::Instance()->Log(Level::Info, "main", "Initialize Log");

    string request;
    const char *isDebug = getenv("debug");
    if (isDebug)
    {
        request = readDRequest();
    }
    else
    {
        request = readRequest();
    }

    if (request.empty())
    {
        Response response;
        response.setBody("{}");
        cout << response.toString();
    }
    else
    {
        Request req(request);
        Response response = req.GetResponse();
        cout << response.toString();
    }

    cin.ignore();
    return 0;
}
