#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "WebBoundary.h"

class WebRequest {
public:
    WebRequest();
    ~WebRequest();
    static std::string parseType(std::string data);
    static std::string parseUri(std::string data);
    std::string parseHeader(std::string data);
    void parseCookies();
    std::vector<std::string> parseHttpSegment(std::string data);
    void parseHttpHeader();
    std::string get(std::string key);
    std::string getHeader(std::string key);
    std::string getCookie(std::string key);
    std::string head;
    std::string uri;
    std::string type;
    std::map<std::string, std::string> header;
    std::map<std::string, std::string> params;
    std::map<std::string, std::string> cookies;
    std::map<std::string, WebBoundary> files;
    WebBoundary getFile(std::string name);
    bool hasFile(std::string name);
};

#endif

