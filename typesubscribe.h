#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H

#include "typebase.h"
#include <vector>

using std::vector;

class Subscribe : public TypeBase
{
  private:
    /* data */
  public:
    void setEmail(const string &email);
    string getEmail();
    string execute(const Header &header, const string &message) override;   
};

#endif //SUBSCRIBE_H