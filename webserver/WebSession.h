/* 
 * File:   WebSession.h
 * Author: joseph
 *
 * Created on July 5, 2009, 6:37 PM
 */

#ifndef _WEBSESSION_H
#define	_WEBSESSION_H

#include "WebRequest.h"
#include "WebResponse.h"

#include <string>
#include <map>

class WebSession {
    public:
        WebSession(WebRequest *request, WebResponse *response);
        WebSession(const WebSession&);
        WebSession();
        ~WebSession();
        std::string get(std::string);
        std::string get(const char*);
        void set(std::string, std::string);
        void unset(std::string);
        void unset(const char*);
        std::string getId();
        void setId(std::string);
        void generateId();
        void create();
        void load();
        std::string id;
        int loaded;
        ParamMap params;
        WebResponse* response;
        WebRequest* request;
};

#endif	/* _WEBSESSION_H */

