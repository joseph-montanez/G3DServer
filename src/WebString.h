/*
Copyright (c) 2009-2010, Joseph Montanez
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the Joseph Montanez nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
    static std::string replace(std::string replace, std::string with, std::string str);
    static std::string htmlEntitiesEncode(std::string str);
    static std::string htmlEntitiesDecode(std::string str);
    std::string trim();
    std::map<std::string, std::string> parseParams();
    std::map<std::string, std::string> parseParams(std::string delimiter1, std::string delimiter2);
    std::map<std::string, std::string> parseHttpHeader(std::string data);
    std::vector<std::string> parseHttpSegment(std::string data);

    std::string data;
};

#endif	/* _WEBSTRING_H */

