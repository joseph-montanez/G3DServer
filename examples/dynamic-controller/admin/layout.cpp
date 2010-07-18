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

namespace admin {

    string layout::header(const char* page_title) {
        return layout::header(page_title, "home", false);
    }

    string layout::header(const char* page_title, bool logged_in) {
        return layout::header(page_title, "home", logged_in);
    }

    string layout::header(const char* page_title, const char* nav_item, bool logged_in) {
        string title = page_title;
        string html;
        html.append("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\
        <html>\
        <head>\
            <meta http-equiv=\"content-type\" content=\"text/html; charset=iso-8859-1\" />\
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

        if (strcmp(nav_item, "dashboard") == 0) {
            html.append("<li><a href=\"/admin/dashboard\" class=\"active\">Dashboard</a></li>");
        } else {
            html.append("<li><a href=\"/admin/dashboard\">Dashboard</a></li>");
        }

        if (strcmp(nav_item, "blog-posts") == 0) {
            html.append("<li><a href=\"/admin/blog-posts\" class=\"active\">Posts</a></li>");
        } else {
            html.append("<li><a href=\"/admin/blog-posts\">Posts</a></li>");
        }

        if (strcmp(nav_item, "dashboard") == 0) {
            html.append("<li><a href=\"/admin/blog-comments\" class=\"active\">Comments</a></li>");
        } else {
            html.append("<li><a href=\"/admin/blog-comments\">Comments</a></li>");
        }

        if (strcmp(nav_item, "upload-example") == 0) {
            html.append("<li><a href=\"/admin/upload-example\" class=\"active\">Upload Example</a></li>");
        } else {
            html.append("<li><a href=\"/admin/upload-example\">Upload Example</a></li>");
        }

        if (logged_in == true) {
            html.append("<li><a href=\"/admin/logout\">logout</a></li>");
        } else {
            html.append("<li><a href=\"/admin\">login</a></li>");
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

    string layout::login(string username, string password, string error) {
        string html;
        html.append("\
            <div class=\"post\">\
                <h4>Admin Login</h4>\
                <div class=\"contentarea\">\
                    " + error + "\
                    <form action=\"/admin/login\" method=\"post\">\
                    Username: <input name=\"username\" value=\"" + username + "\" class=\"input\" /> \
                    Password: <input name=\"password\" value=\"" + password + "\" class=\"input\" type=\"password\" /> \
                    <input value=\"Login\" class=\"submit\" type=\"submit\" /> \
                    </form>\
                </div>\
            </div>\
            <div class=\"divider2\"></div>\
        ");
        return html;
    }

    string layout::search_posts(string query) {
        string html;
        html.append("\
            <div class=\"post\">\
                <h4>Admin Login</h4>\
                <div class=\"contentarea\">\
                    <form action=\"/admin/blog-posts\" method=\"get\">\
                    Query: <input name=\"query\" value=\"" + query + "\" class=\"input\" /> \
                    <input value=\"Search\" class=\"submit\" type=\"submit\" /> \
                    </form>\
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
