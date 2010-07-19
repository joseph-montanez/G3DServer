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
#include "g3dserver/WebServer.h"

/*
 * Controllers
 */
#include "listing.cpp"
#include "edit.cpp"

int main(int argc, char* argv[]) {

    WebServer* server = new WebServer();

    server->port = 8181;
    server->addController("/", new ListingController());
    server->addController("/edit", new EditController());

    server->run();
    delete server;
    return 0;
}
