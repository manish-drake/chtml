#ifndef POSTS_H
#define POSTS_H
#include <fstream>
#include "typebase.h"
#include "typepost.h"

using std::ifstream;
using std::ofstream;

class Posts : public TypeBase
{

    void insert(const Post &post)
    {
        std::vector<Post> oldPosts = read<Post>("posts");
        oldPosts.push_back(post);

        std::vector<Post> newPosts;
        for (auto &oldPost : oldPosts)
        {
            Post newPost;
            newPost.setTitle(oldPost.getTitle());
            newPost.setDtPost(oldPost.getDtPost());
            newPost.setAuthor(oldPost.getAuthor());
            newPost.setPara(oldPost.getPara());
            newPosts.push_back(newPost);
        }

        write("posts", newPosts);
    }

  public:
    string execute(const int &action, const string &message) override
    {
        switch (action)
        {
        case ActionEnum::GET:
        {
            ifstream strm("/home/manish/git/chtml/json/posts.json");
            std::string str((std::istreambuf_iterator<char>(strm)),
                            std::istreambuf_iterator<char>());
            return str;
        }
        break;
        case ActionEnum::INSERT:
        {
            ifstream strm("/home/manish/git/chtml/json/posts.json");
            std::string str((std::istreambuf_iterator<char>(strm)),
                            std::istreambuf_iterator<char>());
            setMessage(str);

            Post pst;
            pst.setMessage(message);

            insert(pst);
            app::logger()->log(Level::Info, "Saving to the disk");
            ofstream ofsPosts("/home/manish/git/chtml/json/posts.json");
            ofsPosts << getMessage();
            ofsPosts.close();
            return "{}";
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
    }
};

#endif //POSTS_H