    #include "typepost.h"
    #include "typeheader.h"

    
    void Post::setId(const string &id)
    {
        mWriteRoot["id"] = id;
    }

    string Post::getId()
    {
        return mReadRoot["id"].asString();
    }

    void Post::setTitle(const string &title)
    {
        mWriteRoot["title"] = title;
    }

    string Post::getTitle() const
    {
        return mReadRoot["title"].asString();
    }

    void Post::setDtPost(const string &dtPost)
    {
        mWriteRoot["dtPost"] = dtPost;
    }

    string Post::getDtPost() const
    {
        return mReadRoot["dtPost"].asString();
    }

    void Post::setAuthor(const string &author)
    {
        mWriteRoot["author"] = author;
    }

    string Post::getAuthor() const
    {
        return mReadRoot["author"].asString();
    }

    void Post::setPara(const string &para)
    {
        mWriteRoot["para"] = para;
    }

    string Post::getPara() const
    {
        return mReadRoot["para"].asString();
    }

    string Post::execute(const Header &header, const string &message)
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
        }
        break;
        case ActionEnum::DELETE:
        {
        }
        break;
        default:
            break;
        }

        return getMessage();
    }