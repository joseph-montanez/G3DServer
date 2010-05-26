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
    found = data.find_first_of(delimiter);
    while(found != std::string::npos){
        if(found > 0){
            string_array.push_back(data.substr(0, found));
        }
        data = data.substr(found + 1);
        found = data.find_first_of(delimiter);
    }
    if(data.length() > 0){
        string_array.push_back(data);
    }
    
    return string_array;
}

std::string WebString::implode(std::string delimiter, std::vector<std::string> segments) {
    std::string result;
    for (int i=0; i < segments.size(); i++) {
        result += segments[i];
        if (i + 1 != segments.size()) {
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
