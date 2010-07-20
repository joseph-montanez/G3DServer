#ifndef _POSTMODEL_CPP
#define	_POSTMODEL_CPP

#include <string>
#include "sqlite3.h"
#include "g3dserver/WebString.h"
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
    int totalPosts;
    
    PostModel() {
        this->totalPosts = -1;
        this->tableName = "posts";
        this->opened = false;
        this->canOpen = true;
        this->initializeDatabase();
        if(this->canOpen) {
            this->checkExistance();
        }
    }
    
    ~PostModel() {
        if(this->canOpen) {
            sqlite3_close(this->db);
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
            // This table does not exist!
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
            int columnType = sqlite3_column_type(stmt, column);
            string value = "";
            if(columnType == SQLITE_TEXT) {
                value = (const char*) sqlite3_column_text(stmt, column);
            } else if (columnType == SQLITE_INTEGER) {
                int ivalue = sqlite3_column_int(stmt, column);
                value = WebString::fromInt(ivalue).c_str();
            }
            string key = sqlite3_column_name(stmt, column);
            row.insert(make_pair(key, value));
        }
        
        return row;
    }
    
    sql_rows_def getPaginatedRows(int start, int end) {
        //int totalRows = this->getTotalPosts();
        sql_rows_def rows;
                
        string query = "";
        query.append("SELECT id, title, created FROM ")
            .append(this->tableName)
            .append(" LIMIT ")
            .append(WebString::fromInt(start))
            .append(", ")
            .append(WebString::fromInt(end));
        
        sqlite3_stmt* stmt;
        int failed;
        
        failed = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, 0);
        
        if(failed != SQLITE_OK) {
            return rows;
        }
        
        rows = this->getRows(stmt);
        
        return rows;
    }
    
    int getTotalPosts() {
        if(this->totalPosts != -1) {
            return this->totalPosts;
        }
        string query = "";
        query.append("SELECT COUNT(*) AS totalPosts FROM ").append(this->tableName);
        
        sqlite3_stmt* stmt;
        int failed;
        
        failed = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, 0);
        
        if(failed != SQLITE_OK) {
            return 0;
        }
        
        sql_rows_def rows = this->getRows(stmt);

        if(rows.size() == 0) {
            return 0;
        }
        
        string totalPosts = this->getRowValue(rows.at(0), "totalPosts");
        this->totalPosts = WebString::toInt(totalPosts);
        
        return this->totalPosts;
    }
    
    void update(string title, string body, int id) {
    
    }
    
    void insert(string title, string body) {
        string query = "";
        query.append("INSERT INTO ")
            .append(this->tableName)
            .append(" (title, body, created) VALUES(?, ?, DATE('now'))");
            
        sqlite3_stmt* stmt;
        int failed;
        
        failed = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, 0);
        
        if(failed == SQLITE_OK) {
            int binded;
            binded = sqlite3_bind_text(stmt, 1, title.c_str(), title.length(), SQLITE_STATIC);
            if(binded != SQLITE_OK) {
                this->error = "Unable to bind title to query";
                return;
            }
            
            binded = sqlite3_bind_text(stmt, 2, body.c_str(), body.length(), SQLITE_STATIC);
            if(binded != SQLITE_OK) {
                this->error = "Unable to bind body to query";
                return;
            }
        } else {
            this->error = "Unable to prepare query";
            return;
        }
        
        int status;
        status = sqlite3_step(stmt);
        if(status != SQLITE_DONE) {
            // Grr figure out the error
            this->error = sqlite3_errmsg(this->db);
            return;
        }
        
        /*
         * If this was transactional we would need a begin and commit :\
        char *errormsg;
        status = sqlite3_exec(db, "COMMIT", 0, 0, &errormsg);
        if(status == SQLITE_ABORT) {
            this->error.append(errormsg);
            sqlite3_free(errormsg);
            return;
        }
        sqlite3_free(errormsg);
        */
    }
    
    sqlite3_int64 lastId() {
        return sqlite3_last_insert_rowid(this->db);
    }
    
    
    sql_row_def get(int id) {
        sql_row_def row;
        string query = "";
        query.append("SELECT * FROM ")
            .append(this->tableName)
            .append(" WHERE id = ? LIMIT 1");
            
        sqlite3_stmt* stmt;
        int failed;
        
        failed = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, 0);
        
        if(failed == SQLITE_OK) {
            int binded = sqlite3_bind_int(stmt, 1, id);
            if(binded != SQLITE_OK) {
                this->error = "Unable to bind to query";
                return row;
            }
        } else {
            return row;
        }
        
        sql_rows_def rows = this->getRows(stmt);

        if(rows.size() != 0) {
            row = rows.at(0);
        }
        
        return row;
    }
};


#endif	/* _POSTMODEL_CPP */
