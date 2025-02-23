#ifndef PASSSERVER_H
#define PASSSERVER_H

#include <string>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <utility>
#include <unistd.h>
#include <crypt.h>
#include "hashtable.h"

class PassServer
{
public:
    PassServer(size_t size = 101);
    ~PassServer();

    bool addUser(std::pair<std::string, std::string> &kv);
    bool addUser(std::pair<std::string, std::string> &&kv);
    bool removeUser(const std::string &k);
    bool changePassword(const std::pair<std::string, std::string> &p, const std::string &newpassword);

    void dump() const;
    size_t size() const;
    bool find(const std::string &user) const;

    bool load(const char *filename);
    bool write_to_file(const char* filename);

private:
    std::string encrypt(const std::string &str);
    HashTable<std::string, std::string> passTable;
};

#endif