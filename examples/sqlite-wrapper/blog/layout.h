/*
 * File:   layout.h
 * Author: joseph
 *
 * Created on October 30, 2009, 9:22 PM
 */

#ifndef _BLOGLAYOUT_H
#define	_BLOGLAYOUT_H

#include "string"
using namespace std;

namespace blog {

    class layout {
    public:
        static string header(const char* page_title);
        static string header(const char* page_title, const char* nav_item);
        static string post(const char* post_title, const char* post_content, const char* post_date);
        static string content(string query);
        static string content(const char* content);
        static string footer();
    private:

    };
}

#endif	/* _BLOGLAYOUT_H */
