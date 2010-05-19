#ifndef WEBRESPONSE_H
#define WEBRESPONSE_H

#include <string>
#include <locale>
#include <map>

typedef std::map<std::string, std::string> WebResponseMap;

class WebResponse {
public:
    WebResponse();
    ~WebResponse();
    std::string generateHeader();
    void setHeader(std::string index, std::string value);
    void setHeader(const char* index, const char* value);
    void setStatus(int status);
    void setContentType(std::string type);
    void setCookie(std::string name, std::string value);
    std::string toString();
    std::string getDate();
    std::string getCookieDate();
    WebResponseMap head;
    std::string body;
    int status;
};

#endif
