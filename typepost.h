#ifndef POST_H
#define POST_H
#include "typebase.h"

class Post : public TypeBase
{
  public:
    inline void setTitle(const string &title)
    {
        mWriteRoot["title"] = title;
    }

    inline string getTitle() const
    {
        return mReadRoot["title"].asString();
    }

    inline void setDtPost(const string &dtPost)
    {
        mWriteRoot["dtPost"] = dtPost;
    }

    inline string getDtPost() const
    {
        return mReadRoot["dtPost"].asString();
    }

    inline void setAuthor(const string &author)
    {
        mWriteRoot["author"] = author;
    }

    inline string getAuthor() const
    {
        return mReadRoot["author"].asString();
    }

    inline void setPara(const string &para)
    {
        mWriteRoot["para"] = para;
    }

    inline string getPara() const
    {
        return mReadRoot["para"].asString();
    }
};

#endif //POST_H