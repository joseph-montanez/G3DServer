#include "layout.h"
#include "../../webserver/WebController.h"

#include "string"
using namespace std;

namespace admin {

    class IndexController : public WebController {
    public:

        void get() {
            string content;
            string admin_id = this->session->get("admin_id");
            bool logged_in = false;

            if (admin_id.length() > 0) {
                logged_in = true;
            }

            this->response->body.append(admin::layout::header("Admin | Gorilla Labs", "home", logged_in));

            content = "you are already logged in";
            if (!logged_in) {
                content = admin::layout::content(
                        admin::layout::login(
                        this->request->get("username"),
                        this->request->get("password"),
                        this->request->get("error")
                        )
                        );
            } else {
                this->response->setStatus(302);
                this->response->setHeader("location", "Location: /admin/blog-posts");
            }

            this->response->body.append(content);
            this->response->body.append(admin::layout::footer());
        }
    };
}
