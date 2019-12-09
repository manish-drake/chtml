#ifndef BLOGCOMMENT_H
#define BLOGCOMMENT_H
#include "typebase.h"
class BlogComment: public TypeBase
{
private:
    /* data */
public:    
    void setName(const string &name);    
    string getName();    
    void setEmail(const string &email);    
    string getEmail();    
    void setComment(const string &comment);    
    string getComment();
};
#endif //BLOGCOMMENT_H