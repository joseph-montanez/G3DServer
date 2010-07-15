/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) joseph montanez 2009 <joseph@>
 *
 * main.cc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <stdio.h>
#include <iostream>
#include <map>

/*
 * Web Server
 */
#include "../webserver/WebServer.h"

/*
 * Controllers
 */
#include "index.cpp"
#include "lucene.cpp"
#include "admin/index.cpp"
#include "admin/login.cpp"
#include "admin/logout.cpp"
#include "admin/dashboard.cpp"
#include "admin/blog/posts.cpp"
#include "admin/blog/comments.cpp"
#include "admin/upload/form.cpp"

int main(int argc, char* argv[]) {

    WebServer* server = new WebServer();

    server->port = 8181;
    server->addController("/", new IndexController());
    server->addController("/test", new WebController("/home/joseph/NetBeansProjects/FireController/dist/Debug/GNU-Linux-x86/libFireController.so"));
    server->addController("/lucene", new LuceneController());
    server->addController("/admin", new admin::IndexController());
    server->addController("/admin/login", new admin::LoginController());
    server->addController("/admin/logout", new admin::LogoutController());
    server->addController("/admin/dashboard", new admin::DashboardController());
    server->addController("/admin/blog-posts", new admin::blog::PostController());
    server->addController("/admin/blog-comments", new admin::blog::CommentController());
    server->addController("/admin/upload-example", new admin::upload::FormController());

    server->run();
    delete server;
    return 0;
}
