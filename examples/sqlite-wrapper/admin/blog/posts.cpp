#include "sqlite3.h"
#include "string"
#include <algorithm>
#include <math.h>

#include "../../../webserver/WebController.h"
#include "../../../webserver/WebString.h"
#include "../../../webserver/SqlRow.h"
#include "../../../webserver/SqlQuery.h"
#include "../layout.h"

using namespace std;

namespace admin {
    namespace blog {

        class PostController : public WebController {
        public:

            void get() {
                string admin_id = this->session->get("admin_id");
                bool logged_in = false;

                if (admin_id.empty()) {
                    this->response->setStatus(301);
                    this->response->setHeader("location", "Location: /admin");
                    return;
                }

                this->append(admin::layout::header("Blog Posts | Admin | Gorilla Labs", "blog-posts", logged_in));
                
                sqlite3* db;
                string content;
                content.append(admin::layout::search_posts(this->request->get("query")));
                int failed = sqlite3_open("testDB.sql", &db);

                if (failed == 0) {
                    int total = 0;
                    int pages = 0;
                    int per_page = 10;
                    int max_page = 10;
                    int current_page = WebString::toInt(this->request->get("p"));
                    int start_page = 0;
                    int end_page = 0;
                    string title = "%" + this->request->get("query") + "%";
                    SqlQuery stmt = SqlQuery(&db);

                    // Get Max Pages
                    stmt.query("SELECT COUNT(entry_id) AS total FROM blog_entries WHERE title LIKE ?");
                    stmt.bind(title);
                    stmt.fetchAll();
                    if (!stmt.failed) {
                        total = WebString::toInt(stmt.rows[0].get("total"));
                        pages = (int) ceil(total / per_page);
                        // Figure out last and first pages to show.
                        start_page = current_page - (max_page / 2);
                        if(start_page < 0) {
                            start_page = 0;
                        }
                        end_page = start_page + (max_page / 2);
                    } else {
                        content.append("Error calculating pagination<br />");
                    }
                    
                    // Pagination
                    for (int i = start_page; i < end_page; i++) {
                        string pageno = WebString::fromInt(i);
                        content.append("<a class='page_number' href='?p=" + pageno + "'>" + pageno + "</a> ");
                    }

                    string query = "SELECT * FROM blog_entries WHERE title LIKE ?";
                    query.append("LIMIT ");
                    query.append(WebString::fromInt(current_page * per_page));
                    query.append(", ");
                    query.append(WebString::fromInt(per_page));

                    stmt = SqlQuery(&db);
                    stmt.query(query.c_str());
                    stmt.bind(title);
                    stmt.fetchAll();


                    if (stmt.failed) {
                        content.append("Failed to query: " + this->intToString(stmt.failed));
                    } else {
                        int row_size = stmt.rows.size();
                        content.append("Total Rows: " + this->intToString(row_size) + "<br />");
                        content.append("<table>");
                        content.append("<tr>");
                        content.append("<th>Title</th>");
                        content.append("<th>Actions</th>");
                        content.append("</tr>");
                        for (int i = 0; i < row_size; i++) {
                            SqlRow row = stmt.rows[i];
                            content.append("<tr>");
                            content.append("<td>" + row.get("title") + "</td>");
                            content.append("<td><a href='/admin/blog-posts/edit?entry_id="
                                + row.get("entry_id") + "'>Edit</a></td>");
                            content.append("</tr>");
                        }
                        content.append("</table>");
                    }
                    sqlite3_close(db);
                } else {
                    content.append("Uhh cant open!");
                }

                this->append(content);
                this->append(admin::layout::footer());
            }
        };
    }
}
