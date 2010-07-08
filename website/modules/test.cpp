#include "../../webserver/WebController.h"
#include <string>

class test : public WebController {
public:
    void get() {
        this->response->body.append("Hello World! 2");
    }
};


// the class factories
extern "C" WebController* create() {
        return new test;
}

extern "C" void destroy(WebController* controller) {
    delete controller;
}
