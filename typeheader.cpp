#include "typeheader.h"

int Header::getAction() const
{
    return mReadRoot["action"].asInt();
}

void Header::setAction(const int &action)
{
    mWriteRoot["action"] = action;
}

string Header::getFile() const
{
    return mReadRoot["file"].asString();
}

void Header::setFile(const string &file)
{
    mWriteRoot["file"] = file;
}

int Header::getType() const
{
    return mReadRoot["type"].asInt();
}

void Header::setType(const int &type)
{
    mWriteRoot["type"] = type;
}

int Header::getMax() const
{
    return mReadRoot["max"].asInt();
}
void Header::setMax(const int &max)
{
    mWriteRoot["max"] = max;
}
string Header::getId() const
{
    return mReadRoot["id"].asString();
}
void Header::setId(const string &id)
{
    mWriteRoot["id"] = id;
}