#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include "ServerSocket.h"
#include "SocketException.h"
#include "WebResponse.h"
#include "WebRequest.h"
#include "WebController.h"
#include "WebSession.h"
#include "WebServer.h"
#include <ctime>
#include <cstdlib>

WebServer::WebServer() {
    this->controllers = new ControllerMap;
    this->sessions = SessionMap();
}

WebServer::~WebServer() {

}

void WebServer::addController(std::string uri, WebController* controller) {
    this->controllers->insert(std::make_pair(uri, controller));
}

void WebServer::run() {
    std::string data, buff;
    int status, isLoaded;
    unsigned int nth;
    size_t found;

    srand(time(0));
    std::cout << "running....\n";

    try {
        // Create the socket
        ServerSocket server(this->port);

        while (true) {
            ServerSocket client;
            server.accept(client);
            nth = 0;
            try {
                WebRequest* request = new WebRequest();
                WebResponse* response = new WebResponse();
                WebController* controller;
                std::map<std::string, WebController*>::iterator iter;
                std::string uri;
                data = "";
                status = MAXRECV;
                // TODO: I need to parse the http header before I read everything.
                while (status == MAXRECV) {
                    buff = "";
                    status = client >> buff;
                    if (status == 500) {
                        found = buff.find_last_of("\n");
                        if (found == 499) {
                            status = 0;
                        }
                    }
                    data += buff;
                    std::cout << "reading ..." << std::endl;
                }
                std::cout << data << std::endl;
                uri = request->parseHeader(data);
                
                std::cout << "CONTENT_TYPE:" << request->getHeader("Content-Type") << std::endl;

                // Create or Load Session
                WebSession session = WebSession(request, response);
                session.load();
                if (this->sessions.find(session.id) != this->sessions.end()) {
                    session = this->sessions[session.id];
                }

                //std::cout << session.id << std::endl;
                iter = this->controllers->find(uri);
                if (iter != this->controllers->end()) {
                    controller = iter->second;
                    controller->response = response;
                    controller->request = request;
                    controller->session = &session;
                    controller->get();
                } else {
                    controller = new WebController();
                    controller->response = response;
                    controller->request = request;
                    controller->response->setStatus(404);
                    controller->response->body.append("<h1>Page Not Found</h1>404");
                }
                std::cout << controller->response->toString() << std::endl;
                std::cout << "writting ..." << std::endl;
                client << controller->response->toString();
                
                delete request;
                delete response;
                
                // TODO: sessions shouldn't always be inited by the server ~_~
                this->sessions[session.id] = session;

            } catch (SocketException& e) {
                std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
            }
        }
    } catch (SocketException& e) {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
}
