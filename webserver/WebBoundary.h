#ifndef WEBBOUNDARY_H
#define WEBBOUNDARY_H

#include <string>
#include <vector>
#include <iostream>
#include <map>

class WebBoundary {
public:
    WebBoundary();
    ~WebBoundary();
    std::string getPath();
    std::string getParameter(std::string key);
    std::string getData();
    std::string path;
    std::map<std::string, std::string> params;
    std::string formData;
    std::string contentType;
    std::string name;
    std::string filename;
};

#endif

