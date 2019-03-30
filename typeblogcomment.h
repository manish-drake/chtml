#ifndef BLOGCOMMENT_H
#define BLOGCOMMENT_H
#include "typebase.h"
class BlogComment: public TypeBase
{
private:
    /* data */
public:
    
    inline void setName(const string &name)
    {
        mWriteRoot["name"] = name;
    }
    
    inline string getName()
    {
        return mReadRoot["name"].asString();
    }
    
    inline void setEmail(const string &email)
    {
        mWriteRoot["email"] = email;
    }
    
    inline string getEmail()
    {
        return mReadRoot["email"].asString();
    }
    
    inline void setComment(const string &comment)
    {
        mWriteRoot["comment"] = comment;
    }
    
    inline string getComment()
    {
        return mReadRoot["comment"].asString();
    }
};
#endif //BLOGCOMMENT_H