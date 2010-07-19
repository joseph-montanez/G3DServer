/* 
 * File:   SqliteResult.h
 * Author: joseph
 *
 * Created on October 26, 2009, 10:59 PM
 */

#ifndef _SQLITERESULT_H
#define	_SQLITERESULT_H

#include <string>
#include <iostream>
#include <map>
#include <sqlite3.h>

typedef std::map<std::string, std::string> ParamMap;

class SqlRow {
public:
    SqlRow(sqlite3_stmt* stmt);
    ~SqlRow();
    std::string get(std::string key);
    void set(std::string key, std::string value);
    ParamMap params;
    sqlite3_stmt* stmt;
};

#endif	/* _SQLITERESULT_H */

