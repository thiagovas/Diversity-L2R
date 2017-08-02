CC=g++
FILE=main.cc

all: build cleanafter

build:
	$(CC) $(FILE) -o main -Wall -std=c++11 -DIL_STD -I/home/lapo/cplex/cplex126/cplex/include -I/home/lapo/cplex/cplex126/concert/include -L/home/lapo/cplex/cplex126/cplex/lib/x86-64_linux/static_pic -L/home/lapo/cplex/cplex126/concert/lib/x86-64_linux/static_pic -lconcert -lilocplex -lcplex -lm -pthread -O2


clean: cleanafter
	rm -rf main

cleanafter:
	rm -rf *.o
	rm -rf *~
