#include "../../webserver/WebController.h"
#include <string>

class test : public WebController {
public:
    void get() {
        
    }
    
    void append(std::string content) {
    
    }
    
    void append(const char* content) {
    
    }
    
    void onMultipartPost() {
    
    }
    
    void onStartup() {
    
    }
};


// the class factories
extern "C" {
    WebController* create() {
        return new test;
    }

    void destroy(WebController* controller) {
        delete controller;
    }
}
