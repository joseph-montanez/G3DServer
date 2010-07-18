/*
Copyright (c) 2009-2010, Joseph Montanez
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the Joseph Montanez nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
