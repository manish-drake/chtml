#ifndef POSTS_H
#define POSTS_H
#include <fstream>
#include "typebase.h"
#include "typepost.h"

using std::ifstream;
using std::ofstream;

class Posts : public TypeBase
{
    string insert(const Post &post);
  public:
    string execute(const Header &header, const string &message) override;    
};

#endif //POSTS_H