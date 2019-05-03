#ifndef POST_H
#define POST_H
#include "typebase.h"

class Post : public TypeBase
{
  public:
    void setId(const string &id);
    string getId() const;
    void setTitle(const string &title);
    string getTitle() const;
    void setDtPost(const string &dtPost);
    string getDtPost() const;
    void setAuthor(const string &author);
    string getAuthor() const;
    void setPara(const string &para);
    string getPara() const;
    void setURL(const string &url);
    string getURL() const;
    string execute(const Header &header, const string &message) override;
    
};

#endif //POST_H