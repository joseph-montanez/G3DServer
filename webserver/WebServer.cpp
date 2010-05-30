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
#include "WebString.h"
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
    int status, isLoaded, bytesRead, hasBoundary, startBoundary, endBoundary, 
        readingBoundary, headerLength;
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
                std::map<std::string, WebController*>::iterator iter = this->controllers->end();;
                std::string uri;
                data = "";
                status = MAXRECV;
                hasBoundary = 0;
                startBoundary = -1;
                endBoundary = -1;
                readingBoundary = 0;
                bytesRead = 0;
                headerLength = 0;
                std::string type = "";
                std::string boundary = "";
                int parseType = 0;
                int parseUri = 0;
                
                while (status == MAXRECV) {
                    buff = "";
                    status = client >> buff;
                    data += buff;
                    bytesRead += status;
                    if (parseType == 0) {
                        parseType = 1;
                        
                        type = WebRequest::parseType(data);
                        if (type == "GET") {
                        
                        } else if (type == "POST") {
                        
                        } else {
                            controller = new WebController();
                            controller->response = response;
                            controller->request = request;
                            controller->response->setStatus(404);
                            controller->response->body.append("<h1>Page Not Found</h1>404");
                            break;
                        }
                    } 
                    
                    if (data.find_last_of("\r\n\r\n") != std::string::npos && type == "GET") {
                        status = 0;
                    }
                    
                    // TODO: Allow Max Recieve Limit to be determined by Controller
                    if (parseUri == 0) {
                        if (data.find("\r\n") != std::string::npos) {
                            uri = WebRequest::parseUri(data);
                            parseUri = 1;
                        }
                    }
                    
                    if (parseUri == 1) {
                        iter = this->controllers->find(uri);
                        if (iter == this->controllers->end()) {
                            // If the controller is not found stop asking for data 
                            // server 404 and close the connection.
                            controller = new WebController();
                            controller->response = response;
                            controller->request = request;
                            controller->response->setStatus(404);
                            controller->response->body.append("<h1>Page Not Found</h1>404");
                            //std::cout << "404 START:" << data << ":END 404" << std::endl;
                            break;
                        }
                        parseUri = 2;
                    }
                    
                    if (parseUri == 2 && data.find("\r\n\r\n") != std::string::npos) {
                        headerLength = data.find("\r\n\r\n") - 4;
                        request->parseHeader(data);
                        std::string contentType = request->getHeader("Content-Type");
                        if(type == "POST" && contentType.find("multipart") != -1) {
                            WebString ws = WebString(contentType);
                            std::vector<std::string> segments = ws.explode(";");
                            segments.erase(segments.begin());
                            ws = WebString(ws.implode(";", segments));
                            ws.trim();
                            boundary = ws.data;
                            if(boundary.length() > 0) {
                                ws = WebString(boundary);
                                segments = ws.explode("=");
                                segments.erase(segments.begin());
                                ws = WebString(ws.implode("=", segments));
                                ws.trim();
                                boundary = ws.data;
                            }
                            if(boundary.length() > 0) {
                                hasBoundary = 1;
                            }
                        }
                        parseUri = 3;
                    }
                    
                    if (hasBoundary == 1 && readingBoundary == 0) {
                        /*
                        std::cout << "boundary-test: " << boundary << std::endl;
                        WebString ws = WebString(data);
                        std::vector<std::string> segments = ws.explode(boundary + "--");
                        
                        std::cout << "Boundry Count: " << segments.size() << std::endl;
                        //std::cout << "upload: " << data << std::endl; 
                        std::cout << "read " << (bytesRead - headerLength) << " of " << request->getHeader("Content-Length") << std::endl; 
                        */
                        int totalBytes = WebString::toInt(request->getHeader("Content-Length"));
                        if (bytesRead - headerLength < totalBytes) {
                            status = MAXRECV;
                        }
                        hasBoundary = 2;
                        continue;
                    }
                    
                }
                //std::cout << data << std::endl;
                if(hasBoundary == 2) {
                    std::cout << data << std::endl;
                    WebString ws = WebString(data);
                    std::vector<std::string> segments = ws.explode("--" + boundary);
                    int boundaryIndex;
                    for (boundaryIndex = 1; boundaryIndex < segments.size(); boundaryIndex++) {
                        std::string segment = segments[boundaryIndex];
                        //std::cout << "Boundary: " << segment << std::endl; 
                        ws = WebString(segment);
                        std::vector<std::string> parts = ws.explode("\r\n\r\n");
                        std::string boundaryHeader = parts[0];
                        parts.erase(parts.begin());
                        segment = ws.implode("\r\n\r\n", parts);
                        std::cout << boundaryHeader << std::endl;
                    }
                }
                
                request->parseHeader(data);

                // Create or Load Session
                WebSession session = WebSession(request, response);
                session.load();
                if (this->sessions.find(session.id) != this->sessions.end()) {
                    session = this->sessions[session.id];
                }

                //std::cout << session.id << std::endl;
                if (iter != this->controllers->end()) {
                    controller = iter->second;
                    controller->response = response;
                    controller->request = request;
                    controller->session = &session;
                    controller->get();
                    
                }
                
                //std::cout << controller->response->toString() << std::endl;
                //std::cout << "writting ..." << std::endl;
                client << controller->response->toString();
                
                delete request;
                delete response;
                
                // TODO: sessions shouldn't always be inited by the server ~_~
                this->sessions[session.id] = session;

            } catch (SocketException& e) {
                //std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
            }
        }
    } catch (SocketException& e) {
        //std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
}
