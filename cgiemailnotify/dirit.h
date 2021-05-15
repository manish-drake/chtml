#ifndef DIRIT_H
#define DIRIT_H
#include <string>
#include <dirent.h>
#include <iostream>
using std::string;
class Dirit
{
private:
    std::string m_root;
public:
    Dirit(const std::string &root):m_root(root)
    {

    }

    template <class cb>
    void Doit(cb cbFile, const std::string &folder = "/")
    {
        DIR *dir;
        struct dirent *ent;
        char foldername[1024] = {0};
        sprintf(foldername, "%s%s", m_root.c_str(), folder.c_str());
        if ((dir = opendir(foldername)) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                char entnm[1024] = {0};
                sprintf(entnm, "%s%s", folder.c_str(), ent->d_name);
                switch (ent->d_type)
                {
                case 4:
                {
                    if ((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..") == 0))
                    {
                        cbFile(entnm, 0);
                    }
                    else
                    {
                        cbFile(entnm, 1);
                        entnm[strlen(entnm)] = '/';
                        Doit(cbFile, entnm);
                    }

                    break;
                }
                case 8:
                default:
                {
                    cbFile(entnm, 2);
                    break;
                }
                }
            }
        }
    }
    ~Dirit()
    {

    }
};
#endif //DIRIT_H