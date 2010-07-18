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
    create_t* create_controller;
    destroy_t* destroy_controller;
    
    // get last mod time
    struct tm* clock;
    struct stat attrib;
    stat(this->dynfile.c_str(), &attrib);
    clock = gmtime(&(attrib.st_mtime));

    // check to see if mod time is
    int lastMod = clock->tm_mday + clock->tm_min + clock->tm_hour + clock->tm_sec;
    std::cout << lastMod;
    /*
    if(lastMod = this->dynfileLastMod) {
        WebController::dynController->request = this->request;
        WebController::dynController->response = this->response;
        WebController::dynController->session = this->session;
        WebController::dynController->get();
        return;
    } else {
        // its an updated file
        destroy_controller(WebController::dynController);
        dlclose(this->dynmodule);
    }
    */
    this->dynfileLastMod = lastMod;

    // load the library
    bool loadableMod = true;
    void* test = dlopen(this->dynfile.c_str(), RTLD_LAZY);
    if (!test) {
        std::cout << "Cannot load library: " << dlerror() << std::endl;
        loadableMod = false;
        // reset errors
        dlerror();
    }

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
        //WebController::dynController = cont;
        this->dynmodule = test;
        destroy_controller(cont);
        dlclose(this->dynmodule);
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
