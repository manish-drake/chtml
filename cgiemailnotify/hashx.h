#ifndef HASHX_H
#define HASHX_H
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "md5hash.h"
#include <sstream>

using namespace std;
using std::string;
class Hashx
{
private:
    const std::string m_hashMapIndex;
    md5hash hasher;
    void resetHashMap(std::map<std::string, std::string> &map)
    {
        std::ifstream infile;
        infile.open(m_hashMapIndex);
        std::string line = "";
        while(std::getline(infile, line))
        {
            std::stringstream ss(line);
            std::string file = "";
            std::string hash = "";
            std::getline(ss, file, ',');
            std::getline(ss, hash, '\n');
            map.insert(std::make_pair(file, hash));
        }
    }
    void saveHashMap(const std::map<std::string, std::string> &map)
    {
        std::ofstream outfile;
        outfile.open(m_hashMapIndex, ios::out | ios::trunc);
        for (auto &pr : map)
        {
            outfile << pr.first << "," << pr.second << std::endl;
        }
        outfile.close();
    }
    std::map<std::string, std::string> m_hashMap;
public:
    Hashx(const char* hashMapFile): m_hashMapIndex(hashMapFile)
    {
        resetHashMap(m_hashMap);
    }
    template<class cb>
    void Exists(std::string strSourceFile, cb addCb)
    {
        std::map<std::string, std::string> &hashMap = m_hashMap;
        std::string hash = hasher.printHash(strSourceFile.c_str());
        if (hashMap.find(strSourceFile) == hashMap.end())
        {
            if(addCb(strSourceFile))
                hashMap.insert(std::make_pair(strSourceFile, hash));
        }
        if (hashMap[strSourceFile] != hash)
        {
            if(addCb(strSourceFile))
                hashMap[strSourceFile] = hash;
        }
    }
    ~Hashx()
    {
        saveHashMap(m_hashMap);
    }
};
#endif //HASHX_H