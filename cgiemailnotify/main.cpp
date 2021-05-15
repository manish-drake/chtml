#include "CSmtp.h"
#include <iostream>
#include "dirit.h"
#include "hashx.h"
#include <thread>
#include <exception>

bool endswith(const char* text, const char* partText)
{
    int len = strlen(partText);
    int mlen = strlen(text);
    if(len > mlen)
        return false;
    const char* q1 = &text[mlen-len];
    int result = strncmp(q1, partText, len);
    return (result == 0);
}
std::string getContents(const char* filename)
{
    char newFilepath[1024] = {0};
    sprintf(newFilepath, "/usr/lib/cgi-bin/json%s", filename);
    std::ifstream infile;
    infile.open(newFilepath);
    std::string contents = "";
    std::string line = "";
    while(std::getline(infile, line))
    {
        contents.append(line);
    }
    infile.close();
    return contents;
}
bool SendMail(const char* newFile)
{

    bool bError = false;

    try
    {
        CSmtp mail;

#define test_office_tls

#if defined(test_gmail_tls)
        mail.SetSMTPServer("smtp.gmail.com",587);
        mail.SetSecurityType(USE_TLS);
#elif defined(test_gmail_ssl)
        mail.SetSMTPServer("smtp.gmail.com",465);
        mail.SetSecurityType(USE_SSL);
#elif defined(test_hotmail_TLS)
        mail.SetSMTPServer("smtp.live.com",25);
        mail.SetSecurityType(USE_TLS);
#elif defined(test_aol_tls)
        mail.SetSMTPServer("smtp.aol.com",587);
        mail.SetSecurityType(USE_TLS);
#elif defined(test_yahoo_ssl)
        mail.SetSMTPServer("plus.smtp.mail.yahoo.com",465);
        mail.SetSecurityType(USE_SSL);
#elif defined(test_office_tls)
        mail.SetSMTPServer("smtp.office365.com",587);
        mail.SetSecurityType(USE_TLS);
#endif

        mail.SetLogin("manish@drake.in");
        mail.SetPassword("Shagun2901#");
        mail.SetSenderName("Manish");
        mail.SetSenderMail("manish@drake.in");
        mail.SetReplyTo("manish@drake.in");
        mail.AddRecipient("verma.manish@live.com");
        mail.SetXPriority(XPRIORITY_NORMAL);
        mail.SetXMailer("The Bat! (v3.02) Professional");


        if(endswith(newFile, ".json"))
        {
            char subject[1024] = {0};
            sprintf(subject, "New Json:%s", newFile);

            mail.SetSubject(subject);

            mail.AddMsgLine("-----Json File Contents-----");
            std::string contents = getContents(newFile);
            mail.AddMsgLine(contents.c_str());
            mail.AddMsgLine("----------------------------");
        }
        else {
            char subject[1024] = {0};
            sprintf(subject, "New document:%s", newFile);

            mail.SetSubject(subject);

            mail.AddMsgLine("New document received!");
            mail.AddMsgLine("Regards,");
            mail.AddMsgLine("Manish");

            char newFilepath[1024] = {0};
            sprintf(newFilepath, "/usr/lib/cgi-bin/json%s", newFile);
            mail.AddAttachment(newFilepath);
        }

        //mail.AddAttachment("c:\\test2.exe");
        //mail.AddAttachment("c:\\test3.txt");
        mail.Send();
    }
    catch(ECSmtp e)
    {
        std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
        bError = true;
    }
    if(!bError)
    {
        std::cout << "Mail was send successfully.\n";
        return true;
    }
    else
    {
        return false;
    }

}
void Run()
{
    try {
        const char *HASH_MAP = "/usr/lib/cgi-bin/hashmap";
        Hashx hashIndex(HASH_MAP);

        const char* repo = "/usr/lib/cgi-bin/json";
        Dirit directory(repo);

        directory.Doit([&hashIndex, &repo](std::string filename, int type)->void{
            if(type == 2)
            {
                std::string src = repo;
                src.append(filename);

                hashIndex.Exists(src, [&filename](std::string src)->bool{
                    return SendMail(filename.c_str());
                });
            }
        });
    }
    catch(std::exception &e)
    {
        std::cout << "error in run: " << e.what() << std::endl;
    }
}
int main()
{
    while(true)
    {
        Run();
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    return 0;
}
