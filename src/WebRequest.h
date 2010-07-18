/*
Copyright (c) 2009-2010, Joseph Montanez
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the Joseph Montanez nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "WebBoundary.h"

class WebRequest {
public:
    WebRequest();
    ~WebRequest();
    static std::string parseType(std::string data);
    static std::string parseUri(std::string data);
    std::string parseHeader(std::string data);
    void parseCookies();
    std::vector<std::string> parseHttpSegment(std::string data);
    void parseHttpHeader();
    std::string get(std::string key);
    std::string getHeader(std::string key);
    std::string getCookie(std::string key);
    std::string head;
    std::string uri;
    std::string type;
    std::map<std::string, std::string> header;
    std::map<std::string, std::string> params;
    std::map<std::string, std::string> cookies;
    std::map<std::string, WebBoundary> files;
    WebBoundary getFile(std::string name);
    bool hasFile(std::string name);
};

#endif

