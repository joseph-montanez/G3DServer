/* 
 * File:   WebString.h
 * Author: joseph
 *
 * Created on July 6, 2009, 1:42 AM
 */

#ifndef _WEBSTRING_H
#define	_WEBSTRING_H

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <cctype>

class WebString : public std::string {
    friend std::ostream & operator<<(std::ostream& output, const WebString& data);
public:
    WebString(const char[]);
    WebString(std::basic_string<char, std::char_traits<char>, std::allocator<char> > data);
    void append(std::string data);
    void append(const char data[]);
    std::string lowercase();
    std::string uppercase();
    std::string urlDecode();
    std::string wordwrap(int width);
    std::vector<std::string> explode(std::string delimiter); 
    std::string implode(std::string delimiter, std::vector<std::string> segments); 
    int toInt();
    static int toInt(std::string number);
    static std::string fromInt(int number);
    std::string trim();
    std::map<std::string, std::string> parseParams();
    std::map<std::string, std::string> parseParams(std::string delimiter1, std::string delimiter2);
    std::map<std::string, std::string> parseHttpHeader(std::string data);
    std::vector<std::string> parseHttpSegment(std::string data);

    std::string data;
};

#endif	/* _WEBSTRING_H */

