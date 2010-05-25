/* 
 * File:   WebSession.cpp
 * Author: joseph
 * 
 * Created on July 5, 2009, 6:37 PM
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
    ParamMap::iterator iter;
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
    ParamMap::iterator iter;
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


