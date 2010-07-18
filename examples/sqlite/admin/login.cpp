
#include "layout.h"
#include "../../webserver/WebController.h"

#include "string"
using namespace std;

namespace admin {

    class LoginController : public WebController {
    public:

        void get() {
            const char* location;

            if (this->session->get("admin_id") != "") {
                location = "Location: /admin/blog-posts";
            } else {
                if (this->request->type == "POST") {
                    if (this->request->get("username") == "admin" && this->request->get("password") == "admin") {
                        this->session->set("admin_id", "1");
                        location = "Location: /admin/blog-posts";
                    } else {
                        location = "Location: /admin?error=Your+username+or+password+is+wrong.";
                    }
                }
            }

            this->response->setStatus(301);
            this->response->setHeader("location", location);
        }
    };
}
