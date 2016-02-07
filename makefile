COMPILE = g++
CPPFLAGS = -std=c++11
WFLAGS = -Wall - Werror -ansi -pedantic

SOURCEDIR = src/

all: rshell

rshell:
	g++ $(CPPFLAGS) (WFLAGS) Main.cpp Parse.cpp -o assignment2
