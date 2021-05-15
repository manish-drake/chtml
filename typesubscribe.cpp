#include "typebase.h"
#include "typesubscribe.h"
#include "typeheader.h"
#include <fstream>

    void Subscribe::setEmail(const string &email)
    {
        mWriteRoot["email"] = email;
    }

    string Subscribe::getEmail()
    {
        return mReadRoot["email"].asString();
    }
    string Subscribe::execute(const Header &header, const string &message)
    {
        UNUSED(header);
        UNUSED(message);
        switch (header.getAction())
        {
        case ActionEnum::GET:
        {
        }
        break;
        case ActionEnum::INSERT:
        {
            std::ofstream subscriptionfile("/usr/lib/cgi-bin/json/subscribe.json", ios::out | ios::app);
            subscriptionfile << message << std::endl;
            subscriptionfile.close();
        }
        break;
        case ActionEnum::SAVE:
        {
        }
        break;        
        case ActionEnum::DELETE:
        {
        }
        case ActionEnum::EDIT:
        {

        }
        break;
        default:
            break;
        }

        return R"({"result": "success"})";
    }
