#ifndef _POSTMODEL_CPP
#define	_POSTMODEL_CPP

#include <string>
#include "sqlite3.h"
#include <vector>
#include <map>
#include <iostream>

using namespace std;


typedef map<std::string,std::string> sql_row_def; 
typedef vector<sql_row_def> sql_rows_def; 

class PostModel {
public:
    bool canOpen;
    bool opened;
    sqlite3* db;
    string tableName;
    string error;
    
    PostModel() {
        this->tableName = "posts";
        this->opened = false;
        this->canOpen = true;
        this->initializeDatabase();
        if(this->canOpen) {
            this->checkExistance();
        }
    }
    
    void initializeDatabase() {
        //date('now')
        int failed = 1;
        if(!this->opened) {
            failed = sqlite3_open("blog.sql", &this->db);
        }
        
        if(failed == SQLITE_OK) {
            this->opened = true;
        } else {
            this->canOpen = false;
        }
    }
    
    sqlite3* getDatabase() {
        return this->db;
    }
    
    bool isOpened() {
        return this->opened;
    }
    
    bool isOpenable() {
        return this->canOpen;
    }
    
    bool createTable() {
        string query = "";
        query.append("CREATE TABLE IF NOT EXISTS ");
        query.append(this->tableName);
        query.append(" (\
            id INTEGER PRIMARY KEY AUTOINCREMENT,\
            title VARCHAR(65) NULL,\
            created TEXT NOT NULL,\
            body TEXT NULL\
        )");
        
        sqlite3_exec(db, "BEGIN", 0, 0, 0);
        int failed = sqlite3_exec(db, query.c_str(), 0, 0, 0);
        sqlite3_exec(db, "COMMIT", 0, 0, 0);
        
        if(failed == SQLITE_OK) {
            return true;
        }
        return false;
    }
    
    void checkExistance() {
        string query = "SELECT name FROM sqlite_master WHERE name = ?";
        sqlite3_stmt* stmt;
        int failed;
        
        failed = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, 0);
        
        if(failed == SQLITE_OK) {
            int binded = sqlite3_bind_text(stmt, 1, this->tableName.c_str(), this->tableName.length(), SQLITE_STATIC);
            if(binded != SQLITE_OK) {
                this->error = "Unable to bind to query";
                return;
            }
        } else {
            return;
        }
        
        sql_rows_def rows = this->getRows(stmt);

        if(rows.size() == 0) {
            // This table does no exist!
            this->createTable();
        }
    }
    
    string getRowValue(sql_row_def row, const char* columnName) {
        sql_row_def::iterator iter;
        string value;
        iter = row.find(columnName);
        if (iter != row.end()) {
            value = iter->second;
        } else {
            value = "";
        }
        
        return value;
    }
    
    sql_rows_def getRows(sqlite3_stmt* stmt) {
        sql_rows_def rows;
        int status;
        
        while (1) {
            status = sqlite3_step(stmt);
            if (status == SQLITE_ROW) {
                rows.push_back(this->getRow(stmt));
            } else if (status == SQLITE_DONE) {
                // All rows finished
                break;
            } else {
                // Some error encountered
                break;
            }
        }
        sqlite3_finalize(stmt);
        
        return rows;
    }
    
    sql_row_def getRow(sqlite3_stmt* stmt) {
        sql_row_def row;
        int columns = sqlite3_column_count(stmt);

        for (int column = 0; column < columns; column++) {
            string value = (const char*) sqlite3_column_text(stmt, column);
            string key = sqlite3_column_name(stmt, column);
            row.insert(make_pair(key, value));
        }
        
        return row;
    }
};


#endif	/* _POSTMODEL_CPP */
