#ifndef CONTACT_H
#define CONTACT_H
#include "typebase.h"
class Contact: public TypeBase
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
    void setProject(const string &project);    
    string getProject();


    string execute(const Header &header, const string &message) override;
};
#endif //CONTACT_H