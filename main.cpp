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
    string request;
    const char *lenStr = getenv("CONTENT_LENGTH");
    int len = -1;
    Logger::Instance()->Log(Level::Info, "main", "Content length: %i", len);
    if (lenStr && (len = atoi(lenStr)) != 0)
    {
        Logger::Instance()->Log(Level::Info, "main", "Content length: %i", len);
        char postData[len + 1] = {0};
        postData[len] = '\n';
        char buffer[len] = {0};

        while (fgets(buffer, len + 1, stdin))
        {
            request.append(buffer);
        }
        Logger::Instance()->Log(Level::Info, "main", "request: %s", request.c_str());
        /*Save to watch for request received*/
        ofstream ofs("/home/manish/git/chtml/post1.json");
        ofs << postData;
        ofs.close();
        /*----------------------------------*/

        return request;
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
    std::cout << "testing"<< std::endl <<std::flush;

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
