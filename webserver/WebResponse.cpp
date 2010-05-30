#include <string>
#include <stdio.h>
#include <iostream>
#include <locale>
#include <map>
#include "WebResponse.h"
#include "WebString.h"
#include "zlib.h"


WebResponse::WebResponse() {
    this->setStatus(200);
    this->setHeader(
            std::string("date"),
            std::string("Date: " + this->getDate())
            );
    this->setContentType("text/html");
    this->setHeader(
            std::string("content-language"),
            std::string("Content-Language: en-us")
            );
    this->setHeader(
            std::string("server"),
            std::string("Server: G3D::WebServer/0.1a (Unix) (Ubuntu 9.10)")
            );
    this->setHeader(
            std::string("cache-control"),
            std::string("Cache-Control: no-cache, must-revalidate, post-check=0, pre-check=0")
            );
    this->setHeader(
            std::string("pragma"),
            std::string("Pragma: no-cache")
            );
    this->setHeader(
            std::string("expires"),
            std::string("Expires: Sat, 26 Jul 1997 05:00:00 GM")
            );
            /*
    this->setHeader(
            std::string("last-modified"),
            std::string("Last-Modified: " + this->getDate())
            );
            */
}

WebResponse::~WebResponse() {
    /* 
	WebResponseMap::reverse_iterator iter;
    for (iter = this->head.rbegin(); iter != this->head.rend(); iter++) {
        delete iter->second;
    }
	*/
}


std::string WebResponse::getDate() {
    time_t timestamp = time(NULL);
    char stringstamp[32];
    // Get Formated Date
    strftime(stringstamp, 32, "%a, %d %b %Y %T %Z", localtime(&timestamp));
    // Convert to std::string
    std::string datestamp;
    datestamp.append(stringstamp);

    return datestamp;
}

std::string WebResponse::getCookieDate() {
    // Expire in 8 hours
    // TODO: This needs to be based off the timezone :(
    time_t timestamp = time(NULL) + 28000 + 28000;
    char stringstamp[33];
    // Get Formated Date
    strftime(stringstamp, 33, "%a, %d-%b-%Y %T GMT", localtime(&timestamp));
    // Convert to std::string
    std::string datestamp;
    datestamp.append(stringstamp);

    return datestamp;
}

void WebResponse::setStatus(int status) {
    char head[32];
    std::string* ok = new std::string();
    std::string index = "status";
    std::string value;
    ok->append("");
    if (status == 200) {
        ok->append("OK");
    } else if (status == 301) {
        ok->append("Moved Permanently");
    }
    sprintf(head, "HTTP/1.1 %i %s", status, ok->c_str());
    delete ok;
    value = std::string(head);
    this->status = status;
    this->setHeader(index, value);
}

void WebResponse::setContentType(std::string type) {
    std::string contentType = std::string("Content-Type: ");
    std::string index = "content-type";
    contentType.append(type);
    this->setHeader(index, contentType);
}

std::string WebResponse::generateHeader() {
    std::string header;
    WebResponseMap::reverse_iterator iter;
    for (iter = this->head.rbegin(); iter != this->head.rend(); iter++) {
        header.append(iter->second);
        header.append("\n");
    }
    header.append("\n");
    return header;
}

void WebResponse::setHeader(const char* index, const char* value) {
    this->setHeader(std::string(index), std::string(value));
}

void WebResponse::setHeader(std::string index, std::string value) {
    WebString lv = index.data();
	lv = lv.lowercase();
	index = lv.data.data();
    this->head[index] = value;
}

void WebResponse::setCookie(std::string name, std::string value) {
    std::string cookie = std::string();
    cookie.append("Set-Cookie: " + name + "=" + value + "; path=/; expires=" + this->getCookieDate());
	this->setHeader(std::string("set-cookie-") + name, cookie);
}

std::string WebResponse::toString() {
    std::string body = this->body;
    std::string output;
    std::string index = "content-length";
    std::string value = std::string();

    if (!body.empty() or this->status == 200) {
        char clen[64];
        
        #ifdef __x86_64__
        unsigned long body_size = (unsigned long) body.size();
        sprintf(clen, "Content-Length: %lu", body_size);
        #else
        sprintf(clen, "Content-Length: %i", body.size());
        #endif
        
        value.append(clen);
    } else {
        value.append("Content-Length: 0");
    }
    this->setHeader(index, value);

    output.append(this->generateHeader());
    output.append(body);
    return output;
}
