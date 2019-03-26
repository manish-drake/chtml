#ifndef TYPEBASE_H
#define TYPEBASE_H
#include <string>
#include <json.h>
using std::string;

#define UNUSED(x) (void)(x)
class TypeBase
{
  protected:
    bool mReadValid;
    bool mWriteValid;
    Json::Reader mReader;
    Json::FastWriter mWriter;
    Json::Value mReadRoot;
    Json::Value mWriteRoot;

  public:
    std::string getMessage(void)
    {
        return mWriter.write(mWriteRoot);
    }

    void setMessage(std::string str)
    {
        if (mReader.parse(str, mReadRoot, false))
        {
            mReadValid = true;
        }
        else
        {
            mReadValid = false;
        }
    }

    Json::Value get(void)
    {
        return mWriteRoot;
    }

    void set(Json::Value obj)
    {
        mReadRoot = obj;
    }
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
            ArrayType tp();
            arr.push_back(tp.set(elem));
        }
        return arr;
    }
    virtual string execute(const string &action, const string &message)
    {
        UNUSED(action);
        UNUSED(message);
        return "{}";
    }

};


#endif //TYPEBASE_H