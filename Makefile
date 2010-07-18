FLAGS = -c -g -Wall

all: libwebserver

clean:
	find . -type f -name "*.so" -exec rm -f {} \;	
	find . -type f -name "*.a" -exec rm -f {} \;	
	find . -type f -name "*.o" -exec rm -f {} \;	
	rm -f libwebserver.so

src/ServerSocket.o: src/ServerSocket.cpp src/ServerSocket.h src/SocketException.h src/Socket.h
	g++ $(FLAGS) src/ServerSocket.cpp -o src/ServerSocket.o
	
src/Socket.o: src/Socket.cpp src/Socket.h
	g++ $(FLAGS) src/Socket.cpp -o src/Socket.o
	
src/WebBoundary.o: src/WebBoundary.cpp src/WebBoundary.h
	g++ $(FLAGS) src/WebBoundary.cpp -o src/WebBoundary.o
	
src/WebController.o: src/WebController.cpp src/WebController.h src/WebResponse.h src/WebSession.h
	g++ $(FLAGS) src/WebController.cpp -o src/WebController.o
	
src/WebRequest.o: src/WebRequest.cpp src/WebRequest.h src/WebString.h
	g++ $(FLAGS) src/WebRequest.cpp -o src/WebRequest.o
	
src/WebResponse.o: src/WebResponse.cpp src/WebResponse.h src/WebString.h
	g++ $(FLAGS) src/WebResponse.cpp -o src/WebResponse.o
	
src/WebServer.o:
	g++ $(FLAGS) src/WebServer.cpp -o src/WebServer.o

src/WebSession.o: src/WebSession.cpp src/WebSession.h src/WebRequest.h src/WebResponse.h src/WebSession.h
	g++ $(FLAGS) src/WebSession.cpp -o src/WebSession.o
	
src/WebString.o: src/WebString.cpp src/WebString.h
	g++ $(FLAGS) src/WebString.cpp -o src/WebString.o

libwebserver:  src/ServerSocket.o src/Socket.o src/WebBoundary.o src/WebController.o src/WebRequest.o src/WebResponse.o src/WebServer.o src/WebSession.o src/WebString.o
	ar rcs libwebserver.a src/ServerSocket.o src/Socket.o src/SqlQuery.o src/SqlRow.o src/WebBoundary.o src/WebController.o src/WebRequest.o src/WebResponse.o src/WebServer.o src/WebSession.o src/WebString.o
    

