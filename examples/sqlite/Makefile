FLAGS = -c -g -Wall

all: sqlite-demo

clean:
	find . -type f -name "*.so" -exec rm -f {} \;	
	find . -type f -name "*.a" -exec rm -f {} \;	
	find . -type f -name "*.o" -exec rm -f {} \;	
	rm -f sqlite-demo	
	rm -f blog.sql
	
sqlite-demo: main.cpp listing.cpp layout.cpp PostModel.cpp edit.cpp
	g++ -g -Wall -lg3dserver -lsqlite3 -o sqlite-demo main.cpp layout.cpp
