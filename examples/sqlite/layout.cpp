/*
* File:   Layout.cpp
* Author: joseph
*
* Created on October 30, 2009, 9:21 PM
*/

#include "layout.h"
#include "string"
#include "string.h"
using namespace std;

string Layout::header(const char* page_title) {
    return Layout::header(page_title, "home");
}

string Layout::header(const char* page_title, const char* nav_item) {
    string title = page_title;
    string html;
    html.append("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\
    <html>\
    <head>\
        <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />\
        <title>" + title + "</title>\
        <meta name=\"keywords\" content=\"\" />\
        <meta name=\"description\" content=\"\" />\
    </head>\
    <body>\
    <div id=\"outer\">\
        <div id=\"header\">\
        <div id=\"headercontent\">\
            <h1>Gorilla<sup>Labs</sup></h1>\
            <h2>Documenting my projects</h2>\
        </div>\
    </div>\
    <div id=\"menu\">\
            <ul>\
    ");

    if (strcmp(nav_item, "home") == 0) {
        html.append("<li><a href=\"/\" class=\"active\">Home</a></li>");
    } else {
        html.append("<li><a href=\"/\">Home</a></li>");
    }

    if (strcmp(nav_item, "edit") == 0) {
        html.append("<li><a href=\"edit\" class=\"active\">New Post</a></li>");
    } else {
        html.append("<li><a href=\"edit\">New Post</a></li>");
    }

    html.append("\
                </ul>\
        </div>\
    ");
    return html;
}

string Layout::post(const char* post_title, const char* post_content, const char* post_date) {
    string html;
    string title = post_title;
    string date = post_date;
    string content = post_content;
    html.append("\
        <div class=\"post\">\
            <h4>" + title + "</h4>\
            <div class=\"contentarea\">\
                <div class=\"details\">Posted on " + date + "</div>    \
                " + content + "\
            </div>\
        </div>\
        <div class=\"divider2\"></div>\
    ");
    return html;
}

string Layout::content(string content) {
    return Layout::content(content.c_str());
}

string Layout::content(const char* content) {
    string html;

    string posts = content;

    html.append("\
    <div id=\"content\">\
        <div id=\"primarycontainer\">\
            <div id=\"primarycontent\">\
                " + posts + "\
            </div>\
        </div>\
        <div id=\"secondarycontent\">\
            <div>\
                <h4>Who is me?</h4>\
                <div class=\"contentarea\">\
                    <!--\
                    <ul class=\"linklist\">\
                        <li><a href=\"#\">Dadadada</a></li>                        \
                        <li><a href=\"#\">Lalalalala</a></li>        \
                    </ul>\
                    -->\
                </div>\
            </div>\
        </div>\
    </div>\
    ");

    return html;
}

string Layout::footer() {
    string html;
    html.append("<div id=\"footer\">\
        <div class=\"left\">&copy; 2009-2010 Gorilla Labs. All rights reserved.</div>\
        <div class=\"right\">Code Monkey likes his Fritos... Code Monkey likes Toa &amp; Mountain Dew</div>\
    </div>\
    </div>\
    </body>\
    </html>\
    ");
    return html;
}
