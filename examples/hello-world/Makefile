FLAGS = -c -g -Wall

all: hello

clean:
	find . -type f -name "*.so" -exec rm -f {} \;	
	find . -type f -name "*.a" -exec rm -f {} \;	
	find . -type f -name "*.o" -exec rm -f {} \;	
	find . -type f -name "*.swp" -exec rm -f {} \;
	rm -f hello
	
hello: 
	g++ -lg3dserver -o hello main.cpp
