#include "WebController.h"
#include <string>
#include <sstream>

WebController::WebController() {}
WebController::~WebController() {}
void WebController::get() {}

void WebController::append(std::string content) {
    this->response->body.append(content);
}
void WebController::append(const char* content) {
    this->response->body.append(content);
}

void WebController::post() {}
void WebController::onMultipartPost() {}
void WebController::onStartup() {}

std::string WebController::intToString(int i) {
    std::string s;
    std::stringstream out;
    out << i;
    s = out.str();
    return s;
}
