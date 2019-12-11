#include "typecareer.h"
#include "typeheader.h"
#include <fstream>

void Career::setName(const string &name)
{
    mWriteRoot["name"] = name;
}

string Career::getName()
{
    return mReadRoot["name"].asString();
}

void Career::setEmail(const string &email)
{
    mWriteRoot["email"] = email;
}

string Career::getEmail()
{
    return mReadRoot["email"].asString();
}

void Career::setPhone(const string &phone)
{
    mWriteRoot["phone"] = phone;
}

string Career::getPhone()
{
    return mReadRoot["phone"].asString();
}

void Career::setMessage(const string &message)
{
    mWriteRoot["message"] = message;
}

string Career::getMessage()
{
    return mReadRoot["message"].asString();
}

string Career::execute(const Header &header, const string &message)
{
    // UNUSED(header);
    // UNUSED(message);
    std::string id = "";
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
        std::string name = getNewId();
        sprintf(fileName, "/usr/lib/cgi-bin/json/career_%s.json", name.c_str());
        std::ofstream strm(fileName);
        strm << message << std::endl;
        strm.close();
        id = name;
    }
    break;
    case ActionEnum::DELETE:
    {
    }
    break;
    default:
        break;
    }

    return id;
}
