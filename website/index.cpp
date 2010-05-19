#include "../webserver/WebController.h"
#include "blog/layout.h"

#include "string"
using namespace std;


class IndexController : public WebController {
public:

    void get() {
        this->response->body.append(blog::layout::header("Gorilla Labs"));
        string content;
        content = blog::layout::post("Hello World", "something", "You are running G3D Webserver 0.1a.");
        content = blog::layout::content(content);
        this->response->body.append(content);
        this->response->body.append(blog::layout::footer());
    }
};
