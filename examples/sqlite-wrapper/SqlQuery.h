/* 
 * File:   SqlQuery.h
 * Author: joseph
 *
 * Created on October 27, 2009, 8:25 PM
 */

#ifndef _SQLQUERY_H
#define	_SQLQUERY_H

#include <sqlite3.h>
#include <vector>
#include <string>
#include "SqlRow.h"

class SqlQuery {
public:
    SqlQuery(sqlite3** db);
    SqlQuery(const SqlQuery& orig);
    void query(const char* query);
    void bind(int number);
    void bind(const char* text, int length);
    void bind(const char* text);
    void bind(std::string text);
    void fetchAll(const char* query);
    void fetchAll();
    void exec(const char* query);
    void exec();
    virtual ~SqlQuery();
    sqlite3** db;
    sqlite3_stmt* stmt;
    char bind_index;
    std::vector<SqlRow> rows;
    int failed;
    int status;
};

#endif	/* _SQLQUERY_H */

