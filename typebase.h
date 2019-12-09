#ifndef TYPEBASE_H
#define TYPEBASE_H
#include <string>
#include "logger.h"
#include "json.h"

using std::string;

#define UNUSED(x) (void)(x)
enum TypeEnum
{
    HEADER = 0,
    POST = 1,
    POSTS = 2,
    BLOGPOST = 3,
    BLOGCOMMENT = 4
};
enum ActionEnum
{
    GET = 0,
    INSERT = 1,
    SAVE = 2,    
    DELETE = 3,
    EDIT = 4
};
class Header;
class TypeBase
{
  protected:
    bool mReadValid;
    bool mWriteValid;
    Json::Reader mReader;
    Json::FastWriter mWriter;
    Json::Value mReadRoot;
    Json::Value mWriteRoot;
    string getNewId();    

  public:
    int typeId() const;
    std::string getMessage(void); 
    void setMessage(std::string str);
    Json::Value get(void);
    void set(Json::Value obj);
    Json::Reader reader;
    Json::Value value;
    virtual string execute(const Header &header, const string &message);

    template <typename ArrayType>
    void write(char const* name, std::vector<ArrayType>& arr)
    {
        mWriteRoot[name]=Json::arrayValue;

        //Need "typename" before "std::vector<arrayType>" because the compiler says it is needed
        for(typename std::vector<ArrayType>::iterator it = arr.begin(); it != arr.end(); ++it)
        {            
            mWriteRoot[name].append(it->get());            
        }
    }  

    template <typename ArrayType>
    std::vector<ArrayType> read(char const* name)
    {
        std::vector<ArrayType> arr;
        auto jsonArr =  mReadRoot[name];
        for(auto &elem: jsonArr)
        {
            ArrayType tp;
            tp.set(elem);
            arr.push_back(tp);
        }
        return arr;
    }
};


#endif //TYPEBASE_H