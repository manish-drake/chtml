#ifndef HEADER_H
#define HEADER_H
#include "typebase.h"


class Header : public TypeBase
{

  public:
    Header();
    ~Header();

    string getAction();
    void setAction(string action);
    string getFile();
    void setFile(string file);
    string getType();
    void setType(string type);
};
#endif //HEADER_H
