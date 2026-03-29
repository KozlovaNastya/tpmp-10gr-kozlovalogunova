all:
	g++ -Iincludes src/main.cpp src/database.cpp -lsqlite3 -o bin/app

run:
	./bin/app
