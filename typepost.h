#ifndef POST_H
#define POST_H
#include "typebase.h"

class Post : public TypeBase
{
  public:
    inline void setId(const string &id);
    inline string getId();
    inline void setTitle(const string &title);
    inline string getTitle() const;
    inline void setDtPost(const string &dtPost);
    inline string getDtPost() const;
    inline void setAuthor(const string &author);
    inline string getAuthor() const;
    inline void setPara(const string &para);
    inline string getPara() const;
    string execute(const Header &header, const string &message) override;
    
};

#endif //POST_H