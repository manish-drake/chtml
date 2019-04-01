#include "typebase.h"

string TypeBase::getNewId()
    {
        time_t t = time(nullptr);
        tm *ltm = localtime(&t);
        char buffer[32] = {0};
        strftime(buffer, 32, "%Y%m%d%H%M%S", ltm);
        return string(buffer);
    }

    int TypeBase::typeId() const  
    {
        return mReadRoot["typeId"].asInt();
    }
    std::string TypeBase::getMessage(void)
    {
        return mWriter.write(mWriteRoot);
    }

    void TypeBase::setMessage(std::string str)
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

    Json::Value TypeBase::get(void)
    {
        return mWriteRoot;
    }

    void TypeBase::set(Json::Value obj)
    {
        mReadRoot = obj;
    }

    template <typename ArrayType>
    void TypeBase::write(char const* name, std::vector<ArrayType>& arr)
    {

        mWriteRoot[name]=Json::arrayValue;

        //Need "typename" before "std::vector<arrayType>" because the compiler says it is needed
        for(typename std::vector<ArrayType>::iterator it = arr.begin(); it != arr.end(); ++it)
        {            
            mWriteRoot[name].append(it->get());            
        }
    }

    template <typename ArrayType>
    std::vector<ArrayType> TypeBase::read(char const* name)
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
    
    string TypeBase::execute(const Header &header, const string &message)
    {
        UNUSED(header);
        UNUSED(message);
        return "{}";
    }