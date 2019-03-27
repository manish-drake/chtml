#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include "typeheader.h"
#include "response.h"
#include "request.h"
#include "log.h"

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
    if (lenStr && (len = atoi(lenStr)) != 0)
    {
        app::logger()->log(Level::Info, "CONTENT_LENGTH: %i", len);
        char postData[len + 1] = {0};
        postData[len] = '\n';
        char buffer[len] = {0};

        while (fgets(buffer, len + 1, stdin))
        {
            request.append(buffer); 
        }
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
    UNUSED(argc);
    UNUSED(argv);
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
        response.AppendLogs();
        cout << response.toString();
    }
    else
    {
        Request req(request);
        Response response = req.GetResponse();
        response.AppendLogs();
        cout << response.toString();
    }

    cin.ignore();
    return 0;
}
