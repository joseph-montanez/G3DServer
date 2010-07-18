FLAGS = -c -g -Wall

all: webware

clean:
	find . -type f -name "*.so" -exec rm -f {} \;	
	find . -type f -name "*.a" -exec rm -f {} \;	
	find . -type f -name "*.o" -exec rm -f {} \;	
	find . -type f -name "*.swp" -exec rm -f {} \;
	rm -f libwebserver.so webware
	
website/admin/blog/posts.o: website/admin/blog/posts.cpp
	g++ $(FLAGS) -o website/admin/blog/posts.o website/admin/blog/posts.cpp

website/admin/blog/comments.o: website/admin/blog/comments.cpp
	g++ $(FLAGS) -o website/admin/blog/comments.o website/admin/blog/comments.cpp

website/admin/upload/form.o: website/admin/upload/form.cpp
	g++ $(FLAGS) -o website/admin/upload/form.o website/admin/upload/form.cpp

website/admin/index.o: website/admin/index.cpp
	g++ $(FLAGS) -o website/admin/index.o website/admin/index.cpp

website/admin/dashboard.o: website/admin/dashboard.cpp
	g++ $(FLAGS) -o website/admin/dashboard.o website/admin/dashboard.cpp

website/admin/layout.o: website/admin/layout.cpp
	g++ $(FLAGS) -o website/admin/layout.o website/admin/layout.cpp

website/admin/login.o: website/admin/login.cpp
	g++ $(FLAGS) -o website/admin/login.o website/admin/login.cpp
	
website/admin/logout.o: website/admin/logout.cpp
	g++ $(FLAGS) -o website/admin/logout.o website/admin/logout.cpp 

website/blog/layout.o: website/blog/layout.cpp
	g++ $(FLAGS) -o website/blog/layout.o website/blog/layout.cpp
	
website/main.o: website/index.o website/lucene.o website/blog/layout.o
	g++ $(FLAGS) -o website/main.o website/main.cpp
	
website/lucene.o: 
	g++ $(FLAGS) -o website/lucene.o website/lucene.cpp
	
webserver/SqlQuery.o: webserver/SqlQuery.cpp webserver/SqlQuery.h webserver/SqlRow.h
	g++ $(FLAGS) -lsqlite3 webserver/SqlQuery.cpp -o webserver/SqlQuery.o
	
webserver/SqlRow.o: webserver/SqlRow.cpp webserver/SqlRow.h
	g++ $(FLAGS) -lsqlite3 webserver/SqlRow.cpp -o webserver/SqlRow.o
	
website/index.o: 
	g++ $(FLAGS) -o website/index.o website/index.cpp
	
website/modules/test.o: website/index.o webserver/WebController.o
	g++ -c -fPIC website/modules/test.cpp 
	g++ -shared -o libtest.so -fPIC test.o webserver/WebController.o
	
webware: libwebserver website/index.o website/main.o website/blog/layout.o website/admin/logout.o website/admin/login.o website/admin/dashboard.o website/admin/index.o website/admin/upload/form.o website/admin/blog/posts.o website/admin/blog/comments.o website/admin/layout.o website/lucene.o website/modules/test.o
	g++ -lclucene-core -lpthread -lsqlite3 -L/usr/local/lib/ -o webware -static libwebserver.a website/admin/blog/comments.o website/admin/blog/posts.o website/admin/upload/form.o website/admin/dashboard.o website/admin/index.o website/admin/layout.o website/admin/login.o website/admin/logout.o website/blog/layout.o website/index.o website/lucene.o website/main.o
