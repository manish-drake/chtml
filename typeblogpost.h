#ifndef BLOGPOST_H
#define BLOGPOST_H

#include "typebase.h"
#include "typeblogcomment.h"
#include <vector>

using std::vector;

class BlogPost : public TypeBase
{
  private:
    /* data */
  public:
    void setUrl(const string &url);
    string getUrl();
    void setPostId(const string &postId);
    string getPostId();   
    void setComments(vector<BlogComment> &comments);
    vector<BlogComment> getComments();   
    string execute(const Header &header, const string &message) override;   
};

#endif //BLOGPOST_H