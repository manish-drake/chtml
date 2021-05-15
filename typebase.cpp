#include "typebase.h"
#include "typepost.h"
#include "typeposts.h"
#include "typeblogpost.h"
#include "typeblogcomment.h"
#include "typecontact.h"
#include "typecareer.h"
#include "typesubscribe.h"

string TypeBase::getNewId()
    {
        time_t t = time(nullptr);
        tm *ltm = localtime(&t);
        char buffer[32] = {0};
        strftime(buffer, 32, "%Y%m%d%H%M%S", ltm);
        return string(buffer);
    }

    int TypeBase::typeId() const  
    {
        return mReadRoot["typeId"].asInt();
    }
    std::string TypeBase::getMessage(void)
    {
        return mWriter.write(mWriteRoot);
    }

    void TypeBase::setMessage(std::string str)
    {
        if (mReader.parse(str, mReadRoot, false))
        {
            mReadValid = true;
        }
        else
        {
            mReadValid = false;
        }
    }

    Json::Value TypeBase::get(void)
    {
        return mWriteRoot;
    }

    void TypeBase::set(Json::Value obj)
    {
        mReadRoot = obj;
    }   
    
    string TypeBase::execute(const Header &header, const string &message)
    {
        UNUSED(header);
        UNUSED(message);
        return "{}";
    }
    std::unique_ptr<TypeBase> TypeBase::Create(const int& typeID)
    {
        switch (typeID)
        {
        case TypeEnum::POSTS:
        {
            Logger::Instance()->Log(Level::Info, "typebase", "Executing Posts action");
            return  std::unique_ptr<TypeBase>(new Posts);
        }
        break;
        case TypeEnum::POST:
        {
            Logger::Instance()->Log(Level::Info, "typebase", "Executing Post action");
            return  std::unique_ptr<TypeBase>(new Posts);
        }
        break;
        case TypeEnum::BLOGPOST:
        {
            Logger::Instance()->Log(Level::Info, "typebase", "Executing BlogPost action");
            return std::unique_ptr<TypeBase>(new BlogPost);
        }
        break;
        case TypeEnum::BLOGCOMMENT:
        {
            Logger::Instance()->Log(Level::Info, "typebase", "Executing BlogComment action");
            return  std::unique_ptr<TypeBase>(new BlogComment);
        }
        break;
        case TypeEnum::CONTACT:
        {
            Logger::Instance()->Log(Level::Info, "typebase", "Executing contact action");
            return  std::unique_ptr<TypeBase>(new Contact);
        }
        break;
        case TypeEnum::CAREER:
        {
            Logger::Instance()->Log(Level::Info, "typebase", "Executing career action");
            return  std::unique_ptr<TypeBase>(new Career);
        }
        break;
        case TypeEnum::SUBSCRIBE:
        {
            Logger::Instance()->Log(Level::Info, "typebase", "Executing subscribe action");
            return  std::unique_ptr<TypeBase>(new Subscribe);
        }
        break;
        default:
            return  std::unique_ptr<TypeBase>(new TypeBase);
            break;
        }

    }