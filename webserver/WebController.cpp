#include "WebController.h"
#include <string>
#include <sstream>
#include <dlfcn.h>

WebController::WebController() {}
WebController::WebController (const char* filename) {
    this->dynfile = filename;
}
WebController::~WebController() {}
void WebController::get() {
    // load the library
    bool loadableMod = true;
    void* test = dlopen(this->dynfile.c_str(), RTLD_LAZY);
    if (!test) {
        std::cout << "Cannot load library: " << dlerror() << std::endl;
        loadableMod = false;
        // reset errors
        dlerror();
    }
    
    create_t* create_controller;
    destroy_t* destroy_controller;
    const char* dlsym_error;
    if (loadableMod) {
        // load the symbols
        create_controller = (create_t*) dlsym(test, "create");
        dlsym_error = dlerror();
        if (dlsym_error) {
            std::cout << "Cannot load symbol create: " << dlsym_error << std::endl;;
            loadableMod = false;
        }
    }
        
    if (loadableMod) {
        destroy_controller = (destroy_t*) dlsym(test, "destroy");
        dlsym_error = dlerror();
        if (dlsym_error) {
            std::cout << "Cannot load symbol destroy: " << dlsym_error << std::endl;
            loadableMod = false;
        }
    }
    
    // create an instance of the class
    if (loadableMod) {
        WebController* cont = create_controller();
        cont->request = this->request;
        cont->response = this->response;
        cont->session = this->session;
        cont->get();
        destroy_controller(cont);
        dlclose(test);
    }
}

void WebController::append(std::string content) {
    this->response->body.append(content);
}
void WebController::append(const char* content) {
    this->response->body.append(content);
}

void WebController::post() {}

std::string WebController::intToString(int i) {
    std::string s;
    std::stringstream out;
    out << i;
    s = out.str();
    return s;
}
