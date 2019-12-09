#include "typeblogcomment.h"

    void BlogComment::setName(const string &name)
    {
        mWriteRoot["name"] = name;
    }
    
    string BlogComment::getName()
    {
        return mReadRoot["name"].asString();
    }
    
    void BlogComment::setEmail(const string &email)
    {
        mWriteRoot["email"] = email;
    }
    
    string BlogComment::getEmail()
    {
        return mReadRoot["email"].asString();
    }
    
    void BlogComment::setComment(const string &comment)
    {
        mWriteRoot["comment"] = comment;
    }
    
    string BlogComment::getComment()
    {
        return mReadRoot["comment"].asString();
    }