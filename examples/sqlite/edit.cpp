#include <string>

#include "g3dserver/WebController.h"
#include "g3dserver/WebString.h"
#include "layout.h"
#include "sqlite3.h"
#include "PostModel.cpp"

using namespace std;

class EditController : public WebController {
public:
    void get() {
        int id = WebString::toInt(this->request->get("id"));
        string title = this->request->get("title");
        string body = this->request->get("body");
        
        string error = "";
        
        PostModel *posts = new PostModel();
        if(posts->canOpen && this->request->type == "POST") {
            // Content was posted!
            if(id != 0) {
                posts->update(title, body, id);
            } else {
                posts->insert(title, body);
                id = posts->lastId();
            }
        }
        error = posts->error;
        
        if(id != 0) {
            sql_row_def row = posts->get(id);
            title = posts->getRowValue(row, "title");
            body = posts->getRowValue(row, "body");
            //title = WebString::htmlEntitiesDecode(title);
            //body = WebString::htmlEntitiesDecode(body);
        }
        
        delete posts;
        
        string html = "";
        html.append(Layout::header("Edit Posts"));
        html.append(WebString::fromInt(id));
        html.append(error);
        html.append("<form method='post'>\
        <table>\
            <tr>\
                <td>Title</td>\
                <td><input type='text' name='title' value='")
                .append(WebString::htmlEntitiesEncode(title))
                .append("' /></td>\
            </tr>\
            <tr>\
                <td>Body</td>\
                <td><textarea name='body'>")
                .append(WebString::htmlEntitiesEncode(body))
                .append("</textarea></td>\
            </tr>\
            <tr>\
                <td colspan='2' align='right'><input type='submit' value='Save' /></td>\
            </tr>\
        </table>\
        </form>\
        ");
        
        this->response->body = html;
    }
};
