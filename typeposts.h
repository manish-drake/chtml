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
    string execute(const int &action, const string &message) override
    {
        switch (action)
        {
        case ActionEnum::GET:
        {
        }
        break;
        case ActionEnum::INSERT:
        {
            Post pst;
            pst.setMessage(message);

            insert(pst);
            app::logger()->log(Level::Info, "Saving to the disk");
            ofstream ofsPosts("/home/manish/git/chtml/json/posts.json");
            ofsPosts << getMessage();
            ofsPosts.close();
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
};

#endif //POSTS_H