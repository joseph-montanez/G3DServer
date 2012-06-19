FLAGS = -c -g -Wall

all: cpl

clean:
	find . -type f -name "*.so" -exec rm -f {} \;	
	find . -type f -name "*.a" -exec rm -f {} \;	
	find . -type f -name "*.o" -exec rm -f {} \;	
	find . -type f -name "*.swp" -exec rm -f {} \;
	rm -f cpl
	
cpl: build.js *.cpp *.html
	rhino build.js
	astyle *.cpp
	rm -f *.orig
	g++ -Wall -g -std=c++0x  -o cpl main.cpp -lg3dserver -ldl
