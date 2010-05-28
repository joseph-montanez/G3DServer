#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "WebRequest.h"
#include "WebString.h"

WebRequest::WebRequest() {
}

WebRequest::~WebRequest() {
}

std::vector<std::string> WebRequest::parseHttpSegment(std::string data) {
    WebString ws = WebString(data);
    std::vector<std::string> segments = ws.explode(":");
    std::string key = "";
    std::string value = "";
    if(segments.size() > 1)
    {
        key = segments[0];
        segments.erase(segments.begin());
    }
    
    if(segments.size() > 0)
    {
        ws = WebString("");
        value = ws.implode(":", segments);
    }
    
    std::vector<std::string> string_array;
    string_array.push_back(key);
    string_array.push_back(value);
    return string_array;
}

void WebRequest::parseHttpHeader() {
    // This is a revamp of parseHeader() to allow file uploads (because its dirty!)
    std::string uri, q, k, v, buffer, data;
    std::vector<std::string> segments;
    std::vector<std::string> string_array;
    std::string delimiter = "\n";
    WebString ws = WebString(this->head);
    
    segments = ws.explode(delimiter);
    for (int i=0; i < segments.size(); i++) {
        ws = WebString(segments[i]);
        segments[i] = ws.trim();
        
        if (segments[i].empty()) {
            return;
        }
        WebString wstr = WebString("");
        string_array = this->parseHttpSegment(segments[i]);
        
        wstr.data = string_array[0];
        std::string key = wstr.trim();
        wstr.data = string_array[1];
        std::string value = wstr.trim();
        
        this->header[key] = value;
    }
}

void WebRequest::parseCookies() {
    std::string uri, q, k, v, buffer, data;
    int stub_length, stub_begin, stub_end;
    data = this->head;
    stub_length = this->head.length();
    stub_begin = this->head.find("Cookie: ");
    if (stub_begin == -1) {
        return;
    }
    q = this->head.substr(stub_begin + 8, stub_length);
    q = q.substr(0, q.find("\n") - 1);
    while (true) {
        stub_length = q.length();
        if (stub_length == 0) {
            break;
        }
        stub_begin = q.find("=");
        stub_end = q.find(";");

        if (stub_end == -1) {
            stub_end = stub_length;
        }

        if (stub_begin > -1 && stub_end > -1) {
            buffer = q.substr(0, stub_end);
            v = "";
            k = "";
            if (stub_begin > -1) {
                k = q.substr(0, stub_begin);
                v = buffer.substr(buffer.find("=") + 1, buffer.length());
            } else {
                k = q;
            }
            if (k.substr(0, 1) == " ") {
                k = k.substr(1, k.length());
            }
            //std::cout << "Key: '" + k + "' Value: '" + v + "'" << std::endl;
            this->cookies[k] = v;
        }
        if (stub_end != stub_length) {
            stub_end++;
        }
        q = q.substr(stub_end, stub_length);
    }
}

std::string WebRequest::parseUri(std::string data) {
    std::string uri = "";
    std::string delimiter = "/";
    std::vector<std::string> segments;
    
    // Take out the GET/POST
    WebString ws = WebString(data);
    segments     = ws.explode(delimiter);
    segments.erase(segments.begin());
    
    
    uri      = ws.implode(delimiter, segments);
    ws       = WebString(uri);
    ws.trim();
    
    // Get the first element and this is the URI
    segments = ws.explode(" ");
    uri      = "/" + segments.front();
    
    return uri;
}

std::string WebRequest::parseType(std::string data) {
    int hasType = data.find("GET");
    std::string type = "GET";
    
    if (hasType == -1) {
        hasType = data.find("POST");
        type = "POST";
    }
    
    if (hasType == -1) {
        type = "";
    }
    
    return type;
}

std::string WebRequest::parseHeader(std::string data) {
    std::string uri, q, k, v, buffer;
    int stub_length, stub_begin, stub_end;
    this->head = data;
    /* Find the GET line */
    stub_length = this->head.length();
    if (stub_length == 0) {
        return uri;
    }
    this->parseCookies();
    this->parseHttpHeader();
    //std::cout << this->head;
    stub_begin = this->head.find("GET");
    this->type = "GET";
    if (stub_begin == -1) {
        /* This is a Post? */
        stub_begin = this->head.find("POST");
        this->type = "POST";
    }
    if (stub_begin == -1) {
        return uri;
    }
    //std::cout << this->type << std::endl;
    stub_end = this->head.substr(stub_begin, stub_length).find("\n");
    if (stub_begin > -1 && stub_end > -1) {
        uri = this->head.substr(stub_begin, stub_end);
    }

    /* Find the request within the GET line */
    stub_length = uri.length();
    if (stub_length == 0) {
        return uri;
    }
    stub_begin = uri.find("/");
    stub_end   = -1;
    if(stub_begin != -1) {
        stub_end = uri.substr(stub_begin, stub_length).find(" ");
    }
    if (stub_begin > -1 && stub_end > -1) {
        uri = uri.substr(stub_begin, stub_end);
    }

    //std::cout <<  "URI: " + uri + "\n" << std::endl;

    /* Find the query within the ? line */
    stub_length = uri.length();
    if (stub_length == 0 && this->type == "GET") {
        return uri;
    }
    stub_begin = uri.find("?");
    if (this->type == "POST") {
        stub_begin = this->head.find("\r\n\r\n");
        //printf("begin: %i\n", stub_begin);
    }

    if (stub_begin == -1) {
        //std::cout << "NO QUERY\n" << std::endl;
        return uri;
    }

    if (this->type == "GET") {
        q = uri.substr(stub_begin + 1, stub_length);
        uri = uri.substr(0, stub_begin);
    } else if (this->type == "POST") {
        stub_length = this->head.length();
        q = this->head.substr(stub_begin + 4, stub_length);
    }

    if(q.length() > 0) {
        WebString ws = WebString(q);
        this->params = ws.parseParams();
    }

    // Iterate through each parameter and url decode them
    ParamMap::iterator iter;
    for(iter = this->params.begin(); iter != this->params.end(); iter++) {
        WebString ws = WebString(iter->second);
        this->params[iter->first] = ws.urlDecode();
    }

    return uri;
}

std::string WebRequest::get(std::string key) {
    ParamMap::iterator iter;
    std::string value;
    iter = this->params.find(key);
    if (iter != this->params.end()) {
        value = iter->second;
    } else {
        value = "";
    }
    return value;
}

std::string WebRequest::getCookie(std::string key) {
    ParamMap::iterator iter;
    std::string value;
    value = "";
    if(this->cookies.size() != 0) {
        iter = this->cookies.find(key);
        if (iter != this->cookies.end()) {
            if(!iter->second.empty()) {
                value = iter->second;
            }
        } 
    }
    return value;
}

std::string WebRequest::getHeader(std::string key) {
    ParamMap::iterator iter;
    std::string value;
    value = "";
    if(this->header.size() != 0) {
        iter = this->header.find(key);
        if (iter != this->header.end()) {
            if(!iter->second.empty()) {
                value = iter->second;
            }
        }
    }
    return value;
}
