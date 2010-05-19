#ifndef _WEBSERVER_H
#define _WEBSERVER_H

#include <map>
#include "WebResponse.h"
#include "WebRequest.h"
#include "WebController.h"
#include "WebSession.h"

typedef std::map<std::string, WebController*> ControllerMap;
typedef std::map<std::string, WebSession> SessionMap;

class WebServer {
public:
    WebServer();
    ~WebServer();
    ControllerMap* controllers;
    unsigned int port;
    SessionMap sessions;
    void run();
    void addController(std::string uri, WebController* controller);
};

#endif /* _WEBSERVER_H */
