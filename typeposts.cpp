#include "typeposts.h"
#include "typeheader.h"

string Posts::insert(const Post &post)
    {
        std::vector<Post> oldPosts = read<Post>("posts");

        string id = getNewId();

        std::vector<Post> newPosts;
        Post newPost;
        newPost.setId(id);
        newPost.setTitle(post.getTitle());
        newPost.setDtPost(post.getDtPost());
        newPost.setAuthor(post.getAuthor());
        newPost.setPara(post.getPara());
        newPost.setURL(post.getURL());
        newPosts.push_back(newPost);

        for (auto &oldPost : oldPosts)
        {
            Post newPost;
            newPost.setId(oldPost.getId());
            newPost.setTitle(oldPost.getTitle());
            newPost.setDtPost(oldPost.getDtPost());
            newPost.setAuthor(oldPost.getAuthor());
            newPost.setPara(oldPost.getPara());
            newPost.setURL(post.getURL());
            newPosts.push_back(newPost);
        }

        write("posts", newPosts);
        return id;
    }

    string Posts::edit(const Post &post)
    {
       std::vector<Post> oldPosts = read<Post>("posts");

        string id = post.getId();

        std::vector<Post> newPosts;
        for (auto &oldPost : oldPosts)
        {
            if(id == oldPost.getId())
            {
                Post newPost;
                newPost.setId(post.getId());
                newPost.setTitle(post.getTitle());
                newPost.setDtPost(post.getDtPost());
                newPost.setAuthor(post.getAuthor());
                newPost.setPara(post.getPara());
                newPost.setURL(post.getURL());
                newPosts.push_back(newPost);
            }
            else{
                Post newPost;
                newPost.setId(oldPost.getId());
                newPost.setTitle(oldPost.getTitle());
                newPost.setDtPost(oldPost.getDtPost());
                newPost.setAuthor(oldPost.getAuthor());
                newPost.setPara(oldPost.getPara());
                newPost.setURL(post.getURL());
                newPosts.push_back(newPost);
            }
        }

        write("posts", newPosts);
        return id;
    }

    string Posts::del(const Post &post)     
    {
        std::vector<Post> oldPosts = read<Post>("posts");

        string id = post.getId();

        std::vector<Post> newPosts;
        for (auto &oldPost : oldPosts)
        {
            if(id != oldPost.getId())
            {
                Post newPost;
                newPost.setId(oldPost.getId());
                newPost.setTitle(oldPost.getTitle());
                newPost.setDtPost(oldPost.getDtPost());
                newPost.setAuthor(oldPost.getAuthor());
                newPost.setPara(oldPost.getPara());
                newPost.setURL(post.getURL());
                newPosts.push_back(newPost);
            }
        }

        write("posts", newPosts);
        return id;
    }

  string Posts::execute(const Header &header, const string &message) 
    {
        switch (header.getAction())
        {
        case ActionEnum::GET:
        {
            ifstream strm("/home/manish/git/chtml/json/posts.json");
            std::string str((std::istreambuf_iterator<char>(strm)),
                            std::istreambuf_iterator<char>());
            if (header.getMax() > 0)
            {
                setMessage(str);
                std::vector<Post> posts = read<Post>("posts");
                std::vector<Post> maxPosts;
                for (auto &oldPost : posts)
                {
                    Post newPost;
                    newPost.setId(oldPost.getId());
                    newPost.setTitle(oldPost.getTitle());
                    newPost.setDtPost(oldPost.getDtPost());
                    newPost.setAuthor(oldPost.getAuthor());
                    newPost.setPara(oldPost.getPara());
                    newPost.setURL(oldPost.getURL());
                    maxPosts.push_back(newPost);
                    if (maxPosts.size() >= header.getMax())
                    {
                        break;
                    }
                }
                write("posts", maxPosts);
                return getMessage();
            }
            else
            {
                return str;
            }
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
            string id = insert(pst);
            ofstream ofsPosts("/home/manish/git/chtml/json/posts.json");
            ofsPosts << getMessage();
            ofsPosts.close();

            return id;
        }
        break;
        case ActionEnum::SAVE:
        {
        }
        break;
        case ActionEnum::EDIT:
        {
            ifstream strm("/home/manish/git/chtml/json/posts.json");
            std::string str((std::istreambuf_iterator<char>(strm)),
                            std::istreambuf_iterator<char>());
            setMessage(str);
            Post pst;
            pst.setMessage(message);
            string result = edit(pst);
            return result;


        }
        break;
        case ActionEnum::DELETE:
        {

            ifstream strm("/home/manish/git/chtml/json/posts.json");
            std::string str((std::istreambuf_iterator<char>(strm)),
                            std::istreambuf_iterator<char>());
            setMessage(str);
            Post pst;
            pst.setMessage(message);
            string result = del(pst);
            return result;

        }
        break;
        default:
            break;
        }
        return "{}";
    }