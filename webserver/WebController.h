#ifndef WEBCONTROLLER_H
#define WEBCONTROLLER_H

#include "WebRequest.h"
#include "WebResponse.h"
#include "WebSession.h"
#include <string>

class WebController {
public:
    WebController();
    ~WebController();
    virtual void get();
    void append(std::string content);
    void append(const char* content);
    void post();
    std::string intToString(int i);
    WebRequest* request;
    WebResponse* response;
    WebSession* session;
};

typedef WebController* create_t();
typedef void destroy_t(WebController* controller);
#endif
