/* 
 * File:   SqlQuery.cpp
 * Author: joseph
 * 
 * Created on October 27, 2009, 8:25 PM
 */

#include "SqlQuery.h"

SqlQuery::SqlQuery(sqlite3** db) {
    this->db = db;
    this->bind_index = 1;
    this->failed = 1;
}

void SqlQuery::query(const char* query) {
    this->failed = sqlite3_prepare_v2(*this->db, query, -1, &this->stmt, 0);
}

void SqlQuery::exec() {
    sqlite3_step(this->stmt);
    sqlite3_finalize(this->stmt);
}

void SqlQuery::exec(const char* query) {
    this->query(query);
    this->exec();
}

void SqlQuery::fetchAll(const char* query) {
    this->query(query);
    this->fetchAll();
}

void SqlQuery::bind(int number) {
    if (!this->failed) {
        sqlite3_bind_int(stmt, this->bind_index, number);
        this->bind_index += 1;
    }
}

void SqlQuery::bind(const char* text, int length) {
    if (!this->failed) {
        sqlite3_bind_text(stmt, this->bind_index, text, length, SQLITE_STATIC);
        this->bind_index += 1;
    }
}

void SqlQuery::bind(const char* text) {
    this->bind((std::string) text);
}

void SqlQuery::bind(std::string text) {
    this->bind(text.c_str(), text.length());
}

void SqlQuery::fetchAll() {
    if (!this->failed) {
        while (1) {
            this->status = sqlite3_step(this->stmt);
            if (this->status == SQLITE_ROW) {
                this->rows.push_back(SqlRow(this->stmt));
            } else if (this->status == SQLITE_DONE) {
                // All rows finished
                break;
            } else {
                // Some error encountered
            }
        }
        sqlite3_finalize(this->stmt);
    } else {
        //Something went wrong
    }
}

SqlQuery::SqlQuery(const SqlQuery& orig) {
}

SqlQuery::~SqlQuery() {
}

