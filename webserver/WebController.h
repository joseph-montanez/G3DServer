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
    virtual void append(std::string content);
    virtual void append(const char* content);
    virtual void onMultipartPost();
    virtual void onStartup();
    void post();
    virtual std::string intToString(int i);
    WebRequest* request;
    WebResponse* response;
    WebSession* session;
};

#endif
