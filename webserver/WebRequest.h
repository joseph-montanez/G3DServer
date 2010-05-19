#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include <string>
#include <iostream>
#include <map>

typedef std::map<std::string, std::string> ParamMap;

class WebRequest {
public:
    WebRequest();
    ~WebRequest();
    std::string parseHeader(std::string data);
    void parseCookies();
    std::string get(std::string key);
    std::string getCookie(std::string key);
    std::string head;
    std::string uri;
    std::string type;
    ParamMap params;
    ParamMap cookies;
};

#endif

