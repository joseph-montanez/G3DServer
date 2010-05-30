FLAGS = -c -g -Wall

all: webware

clean:
	find . -type f -name "*.o" -exec rm -f {} \;
	rm -f libwebserver.so webware

webserver/ServerSocket.o: webserver/ServerSocket.cpp webserver/ServerSocket.h webserver/SocketException.h webserver/Socket.h
	g++ $(FLAGS) webserver/ServerSocket.cpp -o webserver/ServerSocket.o
	
webserver/Socket.o: webserver/Socket.cpp webserver/Socket.h
	g++ $(FLAGS) webserver/Socket.cpp -o webserver/Socket.o
	
webserver/SqlQuery.o: webserver/SqlQuery.cpp webserver/SqlQuery.h webserver/SqlRow.h
	g++ $(FLAGS) webserver/SqlQuery.cpp -o webserver/SqlQuery.o
	
webserver/SqlRow.o: webserver/SqlRow.cpp webserver/SqlRow.h
	g++ $(FLAGS) webserver/SqlRow.cpp -o webserver/SqlRow.o
	
webserver/WebBoundary.o: webserver/WebBoundary.cpp webserver/WebBoundary.h
	g++ $(FLAGS) webserver/WebBoundary.cpp -o webserver/WebBoundary.o
	
webserver/WebController.o: webserver/WebController.cpp webserver/WebController.h webserver/WebResponse.h webserver/WebSession.h
	g++ $(FLAGS) webserver/WebController.cpp -o webserver/WebController.o
	
webserver/WebRequest.o: webserver/WebRequest.cpp webserver/WebRequest.h webserver/WebString.h
	g++ $(FLAGS) webserver/WebRequest.cpp -o webserver/WebRequest.o
	
webserver/WebResponse.o: webserver/WebResponse.cpp webserver/WebResponse.h webserver/WebString.h
	g++ $(FLAGS) webserver/WebResponse.cpp -o webserver/WebResponse.o
	
WebServer.o: webserver/WebServer.cpp webserver/WebServer.h webserver/ServerSocket.h webserver/SocketException.h webserver/WebResponse.h webserver/WebRequest.h webserver/WebController.h webserver/WebSession.h webserver/WebServer.h webserver/WebString.h
	g++ $(FLAGS) webserver/WebServer.cpp -o webserver/WebServer.o

WebSession.o: webserver/WebSession.cpp webserver/WebSession.h webserver/WebRequest.h webserver/WebResponse.h webserver/WebSession.h
	g++ $(FLAGS) webserver/WebSession.cpp -o webserver/WebSession.o
	
WebString.o: webserver/WebString.cpp webserver/WebString.h
	g++ $(FLAGS) webserver/WebString.cpp -o webserver/WebString.o

libwebserver:  webserver/ServerSocket.o webserver/Socket.o webserver/SqlQuery.o webserver/SqlRow.o webserver/WebBoundary.o webserver/WebController.o webserver/WebRequest.o webserver/WebResponse.o webserver/WebServer.o webserver/WebSession.o webserver/WebString.o
	g++ -shared -g -Wall -o libwebserver.so webserver/ServerSocket.o webserver/Socket.o webserver/SqlQuery.o webserver/SqlRow.o webserver/WebBoundary.o webserver/WebController.o webserver/WebRequest.o webserver/WebResponse.o webserver/WebServer.o webserver/WebSession.o webserver/WebString.o
	
website/admin/blog/posts.o:
	g++ $(FLAGS) -o website/admin/blog/posts.o website/admin/blog/posts.cpp

website/admin/blog/comments.o:
	g++ $(FLAGS) -o website/admin/blog/comments.o website/admin/blog/comments.cpp

website/admin/upload/form.o:
	g++ $(FLAGS) -o website/admin/upload/form.o website/admin/upload/form.cpp

website/admin/index.o:
	g++ $(FLAGS) -o website/admin/index.o website/admin/index.cpp

website/admin/dashboard.o: 
	g++ $(FLAGS) -o website/admin/dashboard.o website/admin/dashboard.cpp

website/admin/layout.o:
	g++ $(FLAGS) -o website/admin/layout.o website/admin/layout.cpp

website/admin/login.o:
	g++ $(FLAGS) -o website/admin/login.o website/admin/login.cpp
	
website/admin/logout.o:
	g++ $(FLAGS) -o website/admin/logout.o website/admin/logout.cpp 

website/blog/layout.o:
	g++ $(FLAGS) -o website/blog/layout.o website/blog/layout.cpp
	
website/main.o:
	g++ $(FLAGS) -o website/main.o website/main.cpp
	
website/index.o:
	g++ $(FLAGS) -o website/index.o website/index.cpp

webware: libwebserver website/index.o website/main.o website/blog/layout.o website/admin/logout.o website/admin/login.o website/admin/dashboard.o website/admin/index.o website/admin/upload/form.o website/admin/blog/posts.o website/admin/blog/comments.o website/admin/layout.o 
	g++ -g -lpthread -lsqlite3 -o webware webserver/ServerSocket.o webserver/Socket.o webserver/SqlQuery.o webserver/SqlRow.o webserver/WebBoundary.o webserver/WebController.o webserver/WebRequest.o webserver/WebResponse.o webserver/WebServer.o webserver/WebSession.o webserver/WebString.o website/admin/blog/comments.o website/admin/blog/posts.o website/admin/upload/form.o website/admin/dashboard.o website/admin/index.o website/admin/layout.o website/admin/login.o website/admin/logout.o website/blog/layout.o website/index.o website/main.o
    
