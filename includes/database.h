#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>

class Database {
private:
    sqlite3* db;

public:
    Database(const std::string& path);
    ~Database();


    static int callback(void* NotUsed, int argc, char** argv, char** azColName);


    bool execute(const std::string& sql);


    void getRevenue(const std::string& start, const std::string& end);
    void getTopComposition();
    void getUrgencyStats();
    void getFlowerUsage(const std::string& start, const std::string& end);
    void getCompStats();

    void insertOrder(int comp_id, std::string customer, std::string d_get, std::string d_set, int qty);

    void getOrdersByDate(const std::string& date);
};

#endif

