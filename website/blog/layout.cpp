/*
 * File:   layout.cpp
 * Author: joseph
 *
 * Created on October 30, 2009, 9:21 PM
 */

#include "layout.h"
#include "string"
#include "string.h"
using namespace std;

namespace blog {


    string layout::header(const char* page_title) {
        return blog::layout::header(page_title, "home");
    }

    string layout::header(const char* page_title, const char* nav_item) {
        string title = page_title;
        string html;
        html.append("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\
        <html>\
        <head>\
            <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />\
            <title>" + title + "</title>\
            <meta name=\"keywords\" content=\"\" />\
            <meta name=\"description\" content=\"\" />\
            <link rel=\"stylesheet\" type=\"text/css\" href=\"http://www.gorilla3d.com/labs/default.css\" />\
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
            html.append("<li><a href=\"#\" class=\"active\">Home</a></li>");
        } else {
            html.append("<li><a href=\"#\">Home</a></li>");
        }

        if (strcmp(nav_item, "webserver") == 0) {
            html.append("<li><a href=\"webserver\" class=\"active\">G3D::WebServer</a></li>");
        } else {
            html.append("<li><a href=\"webserver\">G3D::WebServer</a></li>");
        }

        if (strcmp(nav_item, "db") == 0) {
            html.append("<li><a href=\"/admin\" class=\"active\">admin</a></li>");
        } else {
            html.append("<li><a href=\"/admin\">admin</a></li>");
        }

        html.append("\
            </ul>\
    </div>\
        ");
        return html;
    }

    string layout::post(const char* post_title, const char* post_content, const char* post_date) {
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

    string layout::content(string content) {
        return layout::content(content.c_str());
    }

    string layout::content(const char* content) {
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
                            <li><a href=\"#\">Db - MySQLi Wrapper</a></li>                        \
                            <li><a href=\"#\">Pdf Page - Zend_Pdf_Page Wrapper</a></li>        \
                        </ul>\
                        -->\
                    </div>\
                </div>\
            </div>\
        </div>\
        ");

        return html;
    }

    string layout::footer() {
        string html;
        html.append("<div id=\"footer\">\
            <div class=\"left\">&copy; 2009 Gorilla Labs. All rights reserved.</div>\
            <div class=\"right\">Code Monkey likes his Fritos... Code Monkey likes Toa &amp; Mountain Dew</div>\
        </div>\
        </div>\
        </body>\
        </html>\
        ");
        return html;
    }
}
