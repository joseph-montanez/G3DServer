/* 
 * File:   SqliteResult.cpp
 * Author: joseph
 * 
 * Created on October 26, 2009, 10:59 PM
 */

#include "SqlRow.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sqlite3.h>

SqlRow::SqlRow(sqlite3_stmt* stmt) {
    int columns = sqlite3_column_count(stmt);

    this->stmt = stmt;

    for (int column = 0; column < columns; column++) {
        std::string value = (const char*) sqlite3_column_text(stmt, column);
        std::string key = sqlite3_column_name(stmt, column);
        this->set(key, value);
    }
}

SqlRow::~SqlRow() {
}

std::string SqlRow::get(std::string key) {
    ParamMap::iterator iter;
    std::string value;
    iter = this->params.find(key);
    if (iter != this->params.end()) {
        value = iter->second;
    } else {
        value = "";
    }
    return value;
}

void SqlRow::set(std::string key, std::string value) {
    this->params.insert(std::make_pair(key, value));
}