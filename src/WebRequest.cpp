/*
Copyright (c) 2009-2010, Joseph Montanez
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the Joseph Montanez nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
    std::string uri, q, k, v, buffer, data;
    std::vector<std::string> segments;
    std::vector<std::string> string_array;
    std::string delimiter = "\n";
    WebString ws = WebString(this->head);
    
    segments = ws.explode(delimiter);
    for (unsigned int i = 0; i < segments.size(); i++) {
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
    this->head = data;

    this->parseCookies();
    this->parseHttpHeader();

	//-- Parse parameters
	std::string type = this->parseType(data);
	std::string contentType = this->getHeader("Content-Type");

	std::string paramData;
	WebString ws = WebString("");

	if (type == "POST" && contentType == "application/x-www-form-urlencoded") {
		ws = WebString(data);
		std::vector<std::string> parts = ws.explode("\r\n\r\n");
		parts.erase(parts.begin());
		paramData = ws.implode("\r\n\r\n", parts);
	} else if (type == "GET") {
		ws = WebString(data);
		std::vector<std::string> parts = ws.explode("\r\n");
		paramData = parts[0];
		if (paramData.find("?") != std::string::npos) {
			ws = WebString(paramData);
			std::vector<std::string> parts = ws.explode("?");
			paramData = paramData.substr(paramData.find("?"));
			
			if (paramData.find(" ")) {
				paramData = paramData.substr(paramData.find(" "));
			}
		} else {
			paramData = "";
		}
	}

    //ws = WebString(data);
	//std::vector<std::string> parts = ws.explode("\r\n");
	
	//std::cout << parts[0] << "\n" << "param-data:" << paramData << ":end" 
	//    << std::endl << "----------------------" << std::endl;
 
	if (!paramData.empty()) {
		ws = WebString(paramData);
		this->params = ws.parseParams();

		// Iterate through each parameter and url decode them
		std::map<std::string, std::string>::iterator iter;
		for(iter = this->params.begin(); iter != this->params.end(); iter++) {
			WebString ws = WebString(iter->second);
			this->params[iter->first] = ws.urlDecode();
		}
	}

    return this->parseUri(data);
}

std::string WebRequest::get(std::string key) {
    std::map<std::string, std::string>::iterator iter;
    std::string value;
    iter = this->params.find(key);
    if (iter != this->params.end()) {
        value = iter->second;
    } else {
        value = "";
    }
    return value;
}

WebBoundary WebRequest::getFile(std::string name) {
    std::map<std::string, WebBoundary>::iterator iter;
    WebBoundary file;
    iter = this->files.find(name);
    if (iter != this->files.end()) {
        file = iter->second;
    } else {
        file = WebBoundary();
    }
    return file;
}

bool WebRequest::hasFile(std::string name) {
    std::map<std::string, WebBoundary>::iterator iter;
    iter = this->files.find(name);
    if (iter != this->files.end()) {
        return true;
    } else {
        return false;
    }
}

std::string WebRequest::getCookie(std::string key) {
    std::map<std::string, std::string>::iterator iter;
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
    std::map<std::string, std::string>::iterator iter;
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
