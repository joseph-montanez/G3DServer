/* 
 * File:   WebString.cpp
 * Author: joseph
 * 
 * Created on July 6, 2009, 1:42 AM
 */

#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <iostream>

#include "WebString.h"
std::ostream& operator<<(std::ostream& output, const WebString& data) {
    output << data.data;
    return output;
}
WebString::WebString(const char data[]) {
    this->data = data;
}
WebString::WebString(std::basic_string<char,std::char_traits<char>,std::allocator<char> > data) {
    this->data = data;
}
void WebString::append(std::string data) {
    this->data.append(data);
}
void WebString::append(const char data[]) {
    this->data.append(data);
}

std::string WebString::lowercase() {
    std::string value = this->data;
    std::transform(value.begin(), value.end(), value.begin(), std::ptr_fun(::tolower));
    return value;
}

std::string WebString::uppercase() {
    std::string value = this->data;
    std::transform(value.begin(), value.end(), value.begin(), std::ptr_fun(::toupper));
    return value;
}

std::map<std::string, std::string> WebString::parseParams(std::string delimiter1, std::string delimiter2) {
    std::string uri, q, k, v, buffer;
    q = this->data;
    std::map<std::string, std::string> params;
    int stub_length, stub_begin, stub_end;
    
    while (true) {
        stub_length = q.length();
        
        if(stub_length == 0) {
            break;
        }
        
        stub_begin  = q.find(delimiter1);
        stub_end    = q.find(delimiter2);

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
            
            // TODO: this should not be forced, optional trim should be as a parameter.
            if(k.substr(0, 1) == " ") {
                k = k.substr(1);
            }
            params[k] = v;
        }
        if (stub_end != stub_length) {
            stub_end++;
        }
        
        q = q.substr(stub_end, stub_length);
    }
    
    return params;
}

std::map<std::string, std::string> WebString::parseParams() {
    return this->parseParams(std::string("="), std::string("&"));
}

std::string WebString::urlDecode() {
    std::string encoded(this->data);
    std::string::size_type index;
    std::string hex;
    char decode;

    // Replace any %nn values
    while (std::string::npos != (index = encoded.find('%'))) {
        hex = encoded.substr(index + 1, 2);
        std::istringstream charstream(hex);
        int charhex;
        charstream >> std::hex >> charhex;
        decode = char(charhex);
        encoded.replace(index, 3, 1, decode);
    }

    // Replace any + signs with spaces
    while (std::string::npos != (index = encoded.find('+'))) {
        encoded.replace(index, 1, 1, ' ');
    }

    return encoded;
}

int WebString::toInt() {
    return WebString::toInt(this->data);
}

int WebString::toInt(std::string data) {
    return atoi(data.c_str());
}

std::string WebString::fromInt(int i) {
    std::string s;
    std::stringstream out;
    out << i;
    s = out.str();
    return s;
}

std::vector<std::string> WebString::parseHttpSegment(std::string data) {
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

std::map<std::string, std::string> WebString::parseHttpHeader(std::string data) {
    std::map<std::string, std::string> header;
    std::vector<std::string> segments;
    std::vector<std::string> string_array;
    std::string delimiter = "\r\n";
    WebString ws = WebString(data);
    
    segments = ws.explode(delimiter);
    for (size_t i=0; i < segments.size(); i++) {
        ws = WebString(segments[i]);
        segments[i] = ws.trim();
        
        if (segments[i].empty()) {
            break;
        }
        WebString wstr = WebString("");
        string_array = this->parseHttpSegment(segments[i]);
        
        wstr.data = string_array[0];
        std::string key = wstr.trim();
        wstr.data = string_array[1];
        std::string value = wstr.trim();
        
        header[key] = value;
    }
    
    return header;
}

std::string WebString::wordwrap(int width) {
    std::string sentence = this->data;
    std::string::iterator it = sentence.begin();
    std::string::iterator lastSpace = sentence.begin();
    int distanceToWidth = 0;

    while (it != sentence.end()) {
        while (it != sentence.end() && distanceToWidth <= width) {
            distanceToWidth++;
            if (*it == ' ') {
                lastSpace = it;
                if (width == distanceToWidth) {
                    *lastSpace = '\n';
                }
            }
            ++it;
        }
        if (lastSpace != sentence.begin()) {
            *lastSpace = '\n';
        }
        lastSpace = sentence.begin();
        distanceToWidth = 0;
    }
    return sentence;
}

std::vector<std::string> WebString::explode(std::string delimiter) {
    std::vector<std::string> string_array;
    std::string data = this->data;
    int found;
    found = data.find(delimiter);
    
    while (found > -1) {
        if (found > -1) {
            string_array.push_back(data.substr(0, found));
        }
        data = data.substr(found + delimiter.length());
        found = data.find(delimiter);
    }
    if(data.length() > 0){
        string_array.push_back(data);
    }
    
    return string_array;
}

std::string WebString::implode(std::string delimiter, std::vector<std::string> segments) {
    std::string result;
    for (size_t i=0; i < segments.size(); i++) {
        result += segments[i];
        if ((size_t) i + 1 != segments.size()) {
            result += delimiter;
        }
    }
    
    return result;
}

std::string WebString::trim() {
    std::string result(this->data);
    int i,j,start,end;

    //ltrim
    for (i=0; (result[i] != 0 && result[i] <= 32);) {
        i++;
    }
    start = i;

    //rtrim
    for (i = 0,j = 0; result[i] != 0; i++) {
        j = ((result[i] <= 32) ? j + 1 : 0);
    }
    end = i - j;
    result = result.substr(start, end - start);
    
    return result;
}