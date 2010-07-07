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
#include "WebBoundary.h"
#include <ctime>
#include <cstdlib>
#include <bitset>

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
                    data.append(buff);
                    
                    bytesRead += status;
                    if (parseType == 0) {
                        parseType = 1;
                        
                        type = WebRequest::parseType(data);
						request->type = type;
                        if (type == "GET") {
                        
                        } else if (type == "POST") {
                        
                        } else {
                            controller = new WebController();
                            controller->response = response;
                            controller->request = request;
                            controller->response->setStatus(404);
                            controller->response->body.append("<h1>Page Not Found - not a get or post</h1>404");
                            break;
                        }
                        
                    } 

                    if (data.find("\r\n\r\n") > -1 && type == "GET") {
                        status = 0;
                    }
                    
                    // TODO: Allow Max Recieve Limit to be determined by Controller
                    if (parseUri == 0) {
                        if (data.find("\r\n") != std::string::npos) {
                            uri = WebRequest::parseUri(data);
                            parseUri = 1;
                            //std::cout << "uri: " << uri << std::endl;
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
                            controller->response->body.append("<h1>Page Not Found - no controller found!</h1>404");
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
                    
                    if (type == "POST" && !request->getHeader("Content-Length").empty()) {
                        int totalBytes = WebString::toInt(request->getHeader("Content-Length"));
                        //std::cout << (bytesRead - headerLength) / 4 << " of " << totalBytes << std::endl;

                        if ((bytesRead - headerLength) < totalBytes) {
                            status = MAXRECV;
                        }
                    }
                    
					// blah
                    if (hasBoundary == 1 && readingBoundary == 0) {
                        hasBoundary = 2;
                    }
					
                    
                }
                //std::cout << data << "\n----------" << std::endl;
                
                // Parse Uploaded Files
                if(hasBoundary == 2) {
                    //std::cout << data << std::endl;
                    WebString ws = WebString(data);
                    std::vector<std::string> segments = ws.explode("--" + boundary + "\r\n");
                    int boundaryIndex;
                    for (boundaryIndex = 1; boundaryIndex < segments.size(); boundaryIndex++) {
                        std::string segment = segments[boundaryIndex];
                        //std::cout << "Boundary: " << segment << std::endl; 
                        ws = WebString(segment);
                        std::vector<std::string> parts = ws.explode("\r\n\r\n");
                        std::string boundaryHeader = parts[0];
                        parts.erase(parts.begin());
                        segment = ws.implode("\r\n\r\n", parts);
                        
                        std::cout << "bytes" << segment.length() << ":END" << std::endl;
                        
                        // Parse Boundary Header
                        std::map<std::string, std::string> bHead;
                        bHead = ws.parseHttpHeader(boundaryHeader);
                        WebBoundary file = WebBoundary();
                        file.params = bHead;
                        file.formData = segment;
                        file.contentType = file.getParameter("Content-Type");
                        
                        // Parse Disposition into fieldname and filename, 
                        ws = WebString(file.getParameter("Content-Disposition"));
                        std::map<std::string, std::string> params;
                        params = ws.parseParams(std::string("="), std::string(";"));
                        
                        // Iterate through params and remove quotes
                        std::map<std::string, std::string>::iterator iter;
                        for(iter = params.begin(); iter != params.end(); iter++) {
                            std::string value = iter->second;
                            if(value.substr(0, 1) == "\"") {
                                value = value.substr(1);
                            }
                            if(value.substr(value.length() - 1, 1) == "\"") {
                                value = value.substr(0, value.length() - 1);
                            }
                            if (value != iter->second) {
                                params[iter->first] = value;    
                            }
                        }
                        
                        file.filename = params["filename"];
                        file.name = params["name"];
                        if (!file.filename.empty()) {
                            request->files[file.name] = file;
                        }
                    }
                }
                /*
                std::cout << "---------------- DATA IN START ----------------" << std::endl;
                std::cout << data << std::endl;
                std::cout << "---------------- DATA IN END ----------------" << std::endl;
                */
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
                
	            //std::cout << "\nsession id:" << session.id << std::endl;
	            //std::cout << "\nadmin id:" << session.get("admin_id") << std::endl;
                
				std::string out = controller->response->toString();
                //std::cout << "---------------- DATA OUT START ----------------" << std::endl;
                //std::cout << out << std::endl;
                //std::cout << "---------------- DATA OUT END ----------------" << std::endl;
                client << out;
                
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
