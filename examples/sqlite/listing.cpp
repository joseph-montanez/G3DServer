#include <string>

#include "g3dserver/WebController.h"
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
        delete posts;
        
        this->response->body = html;
    } 
};
