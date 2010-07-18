#include "../webserver/WebController.h"
#include "blog/layout.h"
#include "../webserver/SqlRow.h"
#include "../webserver/SqlQuery.h"

#include "string"
#include <dlfcn.h>
#include "sqlite3.h"
using namespace std;


class IndexController : public WebController {
public:

    void get() {
        this->response->body.append(blog::layout::header("Gorilla Labs"));
        std::string content;
        
        // load the library
        bool loadableMod = true;
        void* test = dlopen("./libtest.so", RTLD_LAZY);
        if (!test) {
            std::cout << "Cannot load library: " << dlerror() << std::endl;
            loadableMod = false;
            // reset errors
            dlerror();
        }
        
        create_t* create_controller;
        destroy_t* destroy_controller;
        const char* dlsym_error;
        if (loadableMod) {
            // load the symbols
            create_controller = (create_t*) dlsym(test, "create");
            dlsym_error = dlerror();
            if (dlsym_error) {
                std::cout << "Cannot load symbol create: " << dlsym_error << std::endl;;
                loadableMod = false;
            }
        }
            
        if (loadableMod) {
            destroy_controller = (destroy_t*) dlsym(test, "destroy");
            dlsym_error = dlerror();
            if (dlsym_error) {
                std::cout << "Cannot load symbol destroy: " << dlsym_error << std::endl;
                loadableMod = false;
            }
        }
        
        // create an instance of the class
        if (loadableMod) {
            WebController* cont = create_controller();
            cont->get();
            destroy_controller(cont);
            dlclose(test);
        }
        
        sqlite3* db;
        int failed = sqlite3_open("utf.sql", &db);

        if (failed == 0) {
            SqlQuery stmt = SqlQuery(&db);
            /*
            stmt.exec("CREATE TABLE utf_table (\
                col1 INTEGER NOT NULL,\
                col2 CHAR(25) NULL,\
                col3 VARCHAR(25) NULL,\
                col4 NUMERIC NULL,\
                col5 TEXT(25) NULL,\
                PRIMARY KEY (col1),\
                UNIQUE (col2)\
            )");
            
            sqlite3_exec(db, "BEGIN", 0, 0, 0);
            sqlite3_exec(db, "INSERT INTO utf_table (col3) VALUES('[ˈruskʲɪj jɪˈzɨk]')", 0, 0, 0);
            sqlite3_exec(db, "COMMIT", 0, 0, 0);
            */
            stmt.query("SELECT col1, col3 FROM utf_table WHERE col3 = ?");
            std::string title = "[ˈruskʲɪj jɪˈzɨk]";
            stmt.bind(this->request->get("title"));
            stmt.fetchAll();
            if (!stmt.failed) {
                int row_size = stmt.rows.size();
                for (int i = 0; i < row_size; i++) {
                    SqlRow row = stmt.rows[i];
                    content.append("found id:" + row.get("col1") + ": " + row.get("col3") + "<br />");
                }
            } else {
                content.append("something bad happened");
            }
            sqlite3_close(db);
        } else {
            content.append("failed to open db<br />");
        }
        content.append("<form method='post'><input name='title' /></form><br />" + this->request->get("title"));
        this->response->body.append(content);
        this->response->body.append(blog::layout::footer());
    }
};
