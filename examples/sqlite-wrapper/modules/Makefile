all:
	g++ -c -fPIC test.cpp 
	g++ -shared -o libtest.so -fPIC test.o ../../webserver/WebController.o ../../webserver/WebSession.o ../../webserver/WebRequest.o ../../webserver/WebResponse.o ../../webserver/WebString.o  ../../webserver/WebBoundary.o ../admin/layout.o
