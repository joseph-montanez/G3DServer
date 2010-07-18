/* 
 * File:   layout.h
 * Author: joseph
 *
 * Created on October 30, 2009, 9:22 PM
 */

#ifndef _ADMINLAYOUT_H
#define	_ADMINLAYOUT_H

#include "string"
using namespace std;

namespace admin {

    class layout {
    public:
        static string header(const char* page_title);
        static string header(const char* page_title, bool logged_in);
        static string header(const char* page_title, const char* nav_item, bool logged_in);
        static string post(const char* post_title, const char* post_content, const char* post_date);
        static string login(string username, string password, string error);
        static string search_posts(string query);
        static string content(string query);
        static string content(const char* content);
        static string footer();
    private:

    };
}

#endif	/* _ADMINLAYOUT_H */
