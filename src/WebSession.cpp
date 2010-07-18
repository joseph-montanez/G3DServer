/*
Copyright (c) 2009-2010, Joseph Montanez
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the Joseph Montanez nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "WebRequest.h"
#include "WebResponse.h"
#include "WebSession.h"
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <ctime>
#include <string>
#include <cstdlib>
#include <map>

WebSession::WebSession(WebRequest* request, WebResponse *response) {
    this->request = request;
    this->response = response;
    this->load();
}
WebSession::WebSession(const WebSession&) {

}

WebSession::~WebSession() {
}
WebSession::WebSession() {
}

void WebSession::load() {
    this->id = this->request->getCookie("CPPSESSID");
    this->create();
}

void WebSession::create() {
    if (this->id.length() == 0 || this->id.empty()) {
        this->generateId();
        this->response->setCookie("CPPSESSID", this->id);
    }
}

std::string WebSession::get(const char* key) {
    std::string stdkey = key;
    return this->get(stdkey);
}

std::string WebSession::get(std::string key) {
    std::map<std::string, std::string>::iterator iter;
    std::string value;
    iter = this->params.find(key);
    if (iter != this->params.end()) {
        value = iter->second;
    } else {
        value = "";
    }
    return value;
}

void WebSession::unset(const char* key) {
    std::string stdkey = key;
    this->unset(stdkey);
}

void WebSession::unset(std::string key) {
    std::map<std::string, std::string>::iterator iter;
    std::string value;
    iter = this->params.find(key);
    if (iter != this->params.end()) {
        this->params.erase(iter);
    }
}

void WebSession::set(std::string key, std::string value) {
    this->params.insert(std::make_pair(key, value));
}

void WebSession::generateId() {
    unsigned char nth;
    const char* r [35] = {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
        "n", "o", "p", "q", "r", "s", "t", "u", "v", "x", "y", "z", "1",
        "2", "3", "4", "5", "6", "7", "8", "9", "0"
    };
    this->id = "";
    for (int i = 0; i < 16; i++) {
        nth = rand() % 35;
        this->id.append(r[nth]);
    }
}

std::string WebSession::getId() {
    return this->id;
}

void WebSession::setId(std::string value) {
    this->id = value;
    this->response->setCookie("G3DSESSID", value);
}


