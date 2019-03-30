#ifndef HEADER_H
#define HEADER_H
#include "typebase.h"

class Header : public TypeBase
{

public:
  int getAction() const;
  void setAction(const int &action);
  string getFile() const;
  void setFile(const string &file);
  int getType() const;
  void setType(const int &type);
  int getMax() const;
  void setMax(const int &max);
  string getId() const;
  void setId(const string &id);
};
#endif //HEADER_H
