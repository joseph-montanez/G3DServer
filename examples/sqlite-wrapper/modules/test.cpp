#include "../../webserver/WebController.h"
#include "../admin/layout.h"
#include <string>

using namespace std;

class test : public WebController {
public:
    void get() {
        //this->response->body.append("Hello World! 2 INFINITY I love stuff!");
        string content;
        string admin_id = this->session->get("admin_id");
        bool logged_in = false;

        if (!admin_id.empty()) {
            logged_in = true;
            this->response->setStatus(302);
            this->response->setHeader("location", "Location: /admin/blog-posts");
            return;
        }

        this->response->body.append(admin::layout::header("Admin | Gorilla Labs", "home", logged_in));

        content = admin::layout::content(
            admin::layout::login(
                this->request->get("username"),
                this->request->get("password"),
                this->request->get("error")
            )
        );

        this->response->body.append(content);
        this->response->body.append(admin::layout::footer());
    }
};


// the class factories
extern "C" WebController* create() {
        return new test;
}

extern "C" void destroy(WebController* controller) {
    delete controller;
}
