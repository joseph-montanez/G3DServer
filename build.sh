#!/bin/bash
set +x

webserver_folder="webserver"
webserver_files=(
    "ServerSocket.cpp"
    "Socket.cpp"
    "SqlQuery.cpp"
    "SqlRow.cpp"
    "WebController.cpp"
    "WebCookie.cpp"
    "WebRequest.cpp"
    "WebResponse.cpp"
    "WebServer.cpp"
    "WebSession.cpp"
    "WebString.cpp"
)

# Generate webserver objects
mkdir -p "${webserver_folder}/build"
webserver_shared_files=""
for name in ${webserver_files[@]}
do
    g++ -fPIC -c -g "${webserver_folder}/${name}" -o "${webserver_folder}/build/${name%.cpp}.o"
    webserver_shared_files="${webserver_shared_files} ${webserver_folder}/build/${name%.cpp}.o"
done

# Generate webserver shared library
mkdir -p "${webserver_folder}/dist"
g++ -shared -o -g "${webserver_folder}/dist/libwebserver.so" $webserver_shared_files

website_folder="website"
website_files=(
    "admin/blog/comments.cpp"
    "admin/blog/posts.cpp"
    "admin/upload/form.cpp"
    "admin/dashboard.cpp"
    "admin/index.cpp"
    "admin/layout.cpp"
    "admin/login.cpp"
    "admin/logout.cpp"
    "blog/layout.cpp"
    "index.cpp"
    "main.cpp"
)

# Generate website objects
mkdir -p "${website_folder}/build"
shared_files=""
for name in ${website_files[@]}
do
    mkdir -p "${website_folder}/build/${name%\/*}"
    g++ -c -g "${website_folder}/${name}" -o "${website_folder}/build/${name%.cpp}.o"
    shared_files="${shared_files} ${website_folder}/build/${name%.cpp}.o"
done

# Generate website executable
mkdir -p "${website_folder}/dist"
g++ -g -lpthread -lsqlite3 -o "${website_folder}/dist/website" $webserver_shared_files $shared_files
