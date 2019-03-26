#include "typeheader.h"
Header::Header()
{
}

Header::~Header()
{
}

string Header::getAction()
{
    return mReadRoot["action"].asString();
}

void Header::setAction(string action)
{
    mWriteRoot["action"] = action;
}

string Header::getFile()
{
    return mReadRoot["file"].asString();
}

void Header::setFile(string file)
{
    mWriteRoot["file"] = file;
}

string Header::getType()
{
    return mReadRoot["type"].asString();
}

void Header::setType(string type)
{
    mWriteRoot["type"] = type;
}
