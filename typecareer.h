#ifndef CAREER_H
#define CAREER_H
#include "typebase.h"
class Career: public TypeBase
{
private:
    /* data */
public:    
    void setName(const string &name);    
    string getName();    
    void setEmail(const string &email);    
    string getEmail();      
    void setPhone(const string &phone);    
    string getPhone(); 
    void setMessage(const string &message);    
    string getMessage();


    string execute(const Header &header, const string &message) override;
};
#endif //CAREER_H