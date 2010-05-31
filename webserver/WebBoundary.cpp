#include "WebBoundary.h"
#include <string>
#include <sstream>

WebBoundary::WebBoundary() {}
WebBoundary::~WebBoundary() {}
std::string WebBoundary::getPath() { 
    return std::string(""); 
}
std::string WebBoundary::getData() { 
    return this->formData; 
}
std::string WebBoundary::getParameter(std::string key) { 
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
