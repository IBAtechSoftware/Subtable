# SubTable make file

build:
	mkdir -p bin
	g++ subtable.cpp -c -o ./bin/subtable.o
	ar rvs ./bin/subtable.a ./bin/subtable.o

buildExample:
	g++ example.cpp ./bin/subtable.a -o ./bin/subtableExample