# SubTable make file

build:
	mkdir -p bin
	g++ subtable.cpp -lboost_serialization -o bin/subtable
