#include <string>

#include "g3dserver/WebController.h"
#include "g3dserver/WebString.h"
#include "layout.h"
#include "sqlite3.h"
#include "PostModel.cpp"

using namespace std;

class ListingController : public WebController {
public:
    void get() {
        string html = "";
        html.append(Layout::header("List Posts"));
        
        PostModel *posts = new PostModel();
        if(!posts->canOpen) {
            html.append("Unable to open the database!");
        }
        
        html.append("<table>\
            <tr>\
                <td>Id</td>\
                <td>Title</td>\
                <td>Create</td>\
                <td></td>\
            </tr>\
        ");
        
        // Get total posts 
        int totalPosts = posts->getTotalPosts();
        html.append("Total posts: ").append(WebString::fromInt(totalPosts));
        
        sql_rows_def rows = posts->getPaginatedRows(0, 10);
        int rowcount = rows.size();
        
        if(rowcount == 0) {
            html.append("<tr><td colspan='4'>There are no posts</td></tr>");
        } else {
            for (int i=0; i < rowcount; i++) {
                sql_row_def row = rows[i];
                
                string title = posts->getRowValue(row, "title");
                string id = posts->getRowValue(row, "id");
                string created = posts->getRowValue(row, "created");

                // Encode content
                title = WebString::htmlEntitiesEncode(title);
                id = WebString::htmlEntitiesEncode(id);
                created = WebString::htmlEntitiesEncode(created); 
                
                html.append(this->tr(id, title, created));
            }
        }
        delete posts;
        
        html.append("</table>");
        
        this->response->body = html;
    } 
    
    string tr(string id, string title, string date) {
        string html = "";
        html.append(this->td(id))
            .append(this->td(title))
            .append(this->td(date))
            .append(
                string("<a href='/edit?id=") + id + string("'>Edit</a>")
            );
        return html;
    }
    
    string td(string content) {
        string html = "";
        html.append("<td>").append(content).append("</td>");
        return html;
    }
};
