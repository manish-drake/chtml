#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include "typeheader.h"
#include "response.h"
#include "request.h"

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
    if (lenStr && (len = atoi(lenStr)) != 0)
    {
        char postData[len + 1] = {0};
        postData[len] = '\n';
        fgets(postData, len + 1, stdin);
        return string(postData);
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
        Response resp;
        resp.setBody("{}");
        cout << resp.toString();
    }
    else
    {
        /*
        ofstream ofs("./post.json");
        ofs << request;
        ofs.close();
        */

        Request req(request);
        Response response = req.GetResponse();
    }

    cin.ignore();
    return 0;
}
