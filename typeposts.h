#ifndef POSTS_H
#define POSTS_H
#include <fstream>
#include "typebase.h"
#include "typepost.h"

using std::ofstream;
class Posts : public TypeBase
{

    std::vector<Post> psts;

    void insert(const Post &post)
    {
        Post newPost;
        newPost.setTitle(post.getTitle());
        newPost.setDtPost(post.getDtPost());
        newPost.setAuthor(post.getAuthor());
        newPost.setPara(post.getPara());
        psts.push_back(newPost);
        write("posts", psts);
    }
  public:
    string execute(const string &action, const string &message) override
    {
        if (action == "insert")
        {
            Post pst;
            pst.setMessage(message);

            insert(pst);

            ofstream ofsPosts("./posts.json");
            ofsPosts << getMessage();
            ofsPosts.close();
        }
        if(action == "get")
        {
            
        }
        return getMessage();
    }
};

#endif //POSTS_H