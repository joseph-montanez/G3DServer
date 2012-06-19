#include <string>
#include "g3dserver/WebServer.h"
#include "index.cpp"
#include "demo.cpp"

int main(int argc, char* argv[]) {
    WebServer* server = new WebServer();

    server->port = 8181;
    server->addController("/", new IndexController());
    server->addController("/demo", new DemoController());
    server->run();
    delete server;
    return 0;
}