FLAGS = -c -g -Wall

all: cpl

clean:
	find . -type f -name "*.so" -exec rm -f {} \;	
	find . -type f -name "*.a" -exec rm -f {} \;	
	find . -type f -name "*.o" -exec rm -f {} \;	
	find . -type f -name "*.swp" -exec rm -f {} \;
	rm -f cpl
	
cpl: build.js main.cpp demo.html
	#killall -9 cpl
	rhino build.js
	g++-4.5 -Wall -g -std=c++0x -lg3dserver -o cpl main.cpp
	#./cpl
