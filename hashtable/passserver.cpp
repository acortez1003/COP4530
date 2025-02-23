#include "passserver.h"

PassServer::PassServer(size_t size) : passTable(size) {}

PassServer::~PassServer()
{
    passTable.clear();
}

bool PassServer::addUser(std::pair<std::string, std::string> &kv)
{
    std::string encryptPass = encrypt(kv.second);   // encrypt password
    kv.second = encryptPass;
    
    if(passTable.insert(kv))
        return true;
    return false;
}

bool PassServer::addUser(std::pair<std::string, std::string> &&kv)
{
    std::string encryptPass = encrypt(kv.second);
    kv.second = std::move(encryptPass);
    
    if(passTable.insert(std::move(kv)))
        return true;
    return false;
}

bool PassServer::removeUser(const std::string &k)
{
    if(passTable.remove(k))
        return true;
    return false;
}

bool PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string &newpassword)
{
    if(p.second == newpassword)
        return false;
    else if(!passTable.contains(p.first))
        return false;
    else
    {
        // encrypt to only compare encrypted pass
        std::string oldPass = encrypt(p.second);
        std::string newPass = encrypt(newpassword);
        // test if match
        std::pair<std::string, std::string> oldPair(p.first, oldPass);
        if(passTable.match(oldPair))
        {
            std::pair<std::string, std::string> newPair(p.first, newPass);
            passTable.insert(newPair);
            return true;
        }
        return false;
    }
}

void PassServer::dump() const
{
    passTable.dump();
}

size_t PassServer::size() const
{
    return passTable.size();
}

bool PassServer::find(const std::string &user) const
{
    if(passTable.contains(user))
        return true;
    return false;
}

bool PassServer::load(const char *filename)
{
    if(passTable.load(filename))
        return true;
    return false;
}

bool PassServer::write_to_file(const char* filename)
{
    if(passTable.write_to_file(filename))
        return true;
    return false;
}

std::string PassServer::encrypt(const std::string &str)
{
    char* password = crypt(str.c_str(), "$1$########");
    std::string finalPass = password;
    return finalPass;
}