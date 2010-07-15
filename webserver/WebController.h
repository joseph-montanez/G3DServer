#ifndef WEBCONTROLLER_H
#define WEBCONTROLLER_H

#include "WebRequest.h"
#include "WebResponse.h"
#include "WebSession.h"
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

class WebController {
public:
    WebController();
    WebController(const char* dynLoader);
    ~WebController();
    virtual void get();
    void append(std::string content);
    void append(const char* content);
    void post();
    std::string intToString(int i);
    WebRequest* request;
    WebResponse* response;
    WebSession* session;
    std::string dynfile;
    void* dynmodule;
    int dynfileLastMod;
    static WebController* dynController;
};

typedef WebController* create_t();
typedef void destroy_t(WebController* controller);
#endif
