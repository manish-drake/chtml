#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "webkitformboundary.h"

using namespace std;
int main(void)
{
    const char *lenStr = getenv("CONTENT_LENGTH");
    unsigned int len = -1;
    std::string header, footer;
    bool flag = false;
    unsigned int pt1, pt2;
    if (lenStr && (len = atoi(lenStr)) != 0)
    {
        char* rawdata = static_cast<char*>(malloc(len+1));

        fread(rawdata, len, 1, stdin);

        for (unsigned int i = 0; i <= len - 1; i++)
        {
            if(flag)
            {
                footer.append(&rawdata[i], 1);
                if(std::string::npos != footer.find("\r\n------WebKitFormBoundary"))
                {
                    pt2 = i - 26;
                    break;
                }
            }
            else
            {
                header.append(&rawdata[i], 1);
                if(std::string::npos != header.find("\r\n\r\n"))
                {
                    flag = true;
                    pt1 = i;
                }
            }

        }
        
        WebkitFormBoundary wfb(header);
        if(wfb.IsValid())
        {
            std::string filename = "/usr/lib/cgi-bin/json/";
            filename.append(wfb.GetName());
            filename.append("_");
            filename.append(wfb.GetFilename());
            std::ofstream ostrm(filename, ios::out | ios::binary);
            for(unsigned int i = pt1 + 1; i <= pt2; i++)
            {
                ostrm.write(&rawdata[i], 1);
            }
            ostrm.close();

            free(rawdata); // free memory
        }
        else
        {
            printf("Content-type: text/html\n\n<HTML><PRE>"); // for debug output
            printf("Content Length: %u\n",len);
            printf("Upload unsuccessful");
        }
        

    }
}