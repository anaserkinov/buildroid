#ifndef MAINDATABASE_HPP
#define MAINDATABASE_HPP

#include "Database.hpp"

class MainDatabase {
private:
    static Database database;
public:
    static Database& getDB(){
        return database;
    }
};

#endif