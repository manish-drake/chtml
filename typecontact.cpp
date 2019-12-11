#include "typecontact.h"
#include "typeheader.h"
#include <fstream>

void Contact::setName(const string &name)
{
    mWriteRoot["name"] = name;
}

string Contact::getName()
{
    return mReadRoot["name"].asString();
}

void Contact::setEmail(const string &email)
{
    mWriteRoot["email"] = email;
}

string Contact::getEmail()
{
    return mReadRoot["email"].asString();
}

void Contact::setPhone(const string &phone)
{
    mWriteRoot["phone"] = phone;
}

string Contact::getPhone()
{
    return mReadRoot["phone"].asString();
}

void Contact::setProject(const string &project)
{
    mWriteRoot["project"] = project;
}

string Contact::getProject()
{
    return mReadRoot["project"].asString();
}

string Contact::execute(const Header &header, const string &message)
{
    // UNUSED(header);
    // UNUSED(message);
    switch (header.getAction())
    {
    case ActionEnum::GET:
    {
    }
    break;
    case ActionEnum::INSERT:
    {
    }
    break;
    case ActionEnum::SAVE:
    {
        char fileName[64] = {0};
        sprintf(fileName, "/usr/lib/cgi-bin/json/contact_%s.json", getNewId().c_str());
        std::ofstream strm(fileName);
        strm << message << std::endl;
        strm.close();
    }
    break;
    case ActionEnum::DELETE:
    {
    }
    break;
    default:
        break;
    }

    return "{'result'='success'}";
}
