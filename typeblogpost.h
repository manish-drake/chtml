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
    inline void setUrl(const string &url)
    {
        mWriteRoot["url"] = url;
    }

    inline string getUrl()
    {
        return mReadRoot["url"].asString();
    }

    inline void setPostId(const string &postId)
    {
        mWriteRoot["postId"] = postId;
    }

    inline string getPostId()
    {
        return mReadRoot["postId"].asString();
    }
    inline void setComments(vector<BlogComment> &comments)
    {
        write<BlogComment>("comments", comments);
    }

    inline vector<BlogComment> getComments()
    {
        vector<BlogComment> comments = read<BlogComment>("comments");
        return comments;
    }
    string execute(const Header &header, const string &message) override
    {
        UNUSED(header);
        UNUSED(message);
        switch (header.getAction())
        {
        case ActionEnum::GET:
        {
            char fileName[128] = {0};
            sprintf(fileName, "/home/manish/git/chtml/json/blogpost_%s.json", header.getId().c_str());
            ifstream strm(fileName);
            std::string str((std::istreambuf_iterator<char>(strm)),
                            std::istreambuf_iterator<char>());
            return str;
        }
        break;
        case ActionEnum::INSERT:
        {
            char fileName[128] = {0};
            sprintf(fileName, "/home/manish/git/chtml/json/blogpost_%s.json", header.getId().c_str());
            ifstream strm(fileName);
            std::string str((std::istreambuf_iterator<char>(strm)),
                            std::istreambuf_iterator<char>());
            setMessage(str);
            BlogPost newBlogPost;
            newBlogPost.setUrl(getUrl());
            newBlogPost.setPostId(getPostId());
            Logger::Instance()->Log(Level::Info, "blogpost", "postId: %s", getPostId().c_str());
            vector<BlogComment> oldComments = getComments();
            vector<BlogComment> newComments;

            BlogComment messageComment;
            messageComment.setMessage(message);

            BlogComment newComment;
            newComment.setName(messageComment.getName());
            Logger::Instance()->Log(Level::Info, "blogpost", "name: %s", messageComment.getName().c_str());
            newComment.setEmail(messageComment.getEmail());
            newComment.setComment(messageComment.getComment());
            newComments.push_back(newComment);

            for (auto &blogComment : oldComments)
            {
                BlogComment comment;
                comment.setName(blogComment.getName());
                comment.setEmail(blogComment.getEmail());
                Logger::Instance()->Log(Level::Info, "blogpost", "email: %s", blogComment.getEmail().c_str());
                comment.setComment(blogComment.getComment());
                newComments.push_back(comment);
            }
            newBlogPost.setComments(newComments);

            ofstream ofsPosts(fileName);
            ofsPosts << newBlogPost.getMessage();
            ofsPosts.close();
        }
        break;
        case ActionEnum::SAVE:
        {
            setMessage(message);
            BlogPost newBlogPost;
            newBlogPost.setUrl(getUrl());
            newBlogPost.setPostId(getPostId());
            vector<BlogComment> comments = getComments();
            newBlogPost.setComments(comments);
            char fileName[128] = {0};
            sprintf(fileName, "/home/manish/git/chtml/json/blogpost_%s.json", getPostId().c_str());
            ofstream ofsPosts(fileName);
            ofsPosts << newBlogPost.getMessage();
            ofsPosts.close();
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

#endif //BLOGPOST_H