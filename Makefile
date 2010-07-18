FLAGS = -c -g -Wall -fPIC

all: libg3dserver.so

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
	g++ $(FLAGS) -ldl src/WebController.cpp -o src/WebController.o
	
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

libg3dserver.so:  src/ServerSocket.o src/Socket.o src/WebBoundary.o src/WebController.o src/WebRequest.o src/WebResponse.o src/WebServer.o src/WebSession.o src/WebString.o
	g++ -ldl -shared -Wl,-soname,libg3dserver.so.1 -o libg3dserver.so.1.0 src/ServerSocket.o src/Socket.o src/WebBoundary.o src/WebController.o src/WebRequest.o src/WebResponse.o src/WebServer.o src/WebSession.o src/WebString.o

install:
	mkdir -p /usr/include/g3dserver
	cp src/ServerSocket.cpp /usr/include/g3dserver
	cp src/ServerSocket.h /usr/include/g3dserver
	cp src/Socket.cpp /usr/include/g3dserver
	cp src/SocketException.h /usr/include/g3dserver
	cp src/Socket.h /usr/include/g3dserver
	cp src/WebBoundary.cpp /usr/include/g3dserver
	cp src/WebBoundary.h /usr/include/g3dserver
	cp src/WebController.cpp /usr/include/g3dserver
	cp src/WebController.h /usr/include/g3dserver
	cp src/WebCookie.cpp /usr/include/g3dserver
	cp src/WebCookie.h /usr/include/g3dserver
	cp src/WebRequest.cpp /usr/include/g3dserver
	cp src/WebRequest.h /usr/include/g3dserver
	cp src/WebResponse.cpp /usr/include/g3dserver
	cp src/WebResponse.h /usr/include/g3dserver
	cp src/WebServer.cpp /usr/include/g3dserver
	cp src/WebServer.h /usr/include/g3dserver
	cp src/WebSession.cpp /usr/include/g3dserver
	cp src/WebSession.h /usr/include/g3dserver
	cp src/WebString.cpp /usr/include/g3dserver
	cp src/WebString.h /usr/include/g3dserver
	cp libg3dserver.so.1.0 /usr/lib
	rm -f /usr/lib/libg3dserver.so
	rm -f /usr/lib/libg3dserver.so.1
	ln /usr/lib/libg3dserver.so.1.0 /usr/lib/libg3dserver.so
	ln /usr/lib/libg3dserver.so.1.0 /usr/lib/libg3dserver.so.1
	

