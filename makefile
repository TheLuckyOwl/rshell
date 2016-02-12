COMPILE = g++
CPPFLAGS = -std=c++11
WFLAGS = -Wall -Werror -ansi -pedantic

SOURCEDIR = src/

all: rshell

rshell:
	g++ $(WFLAGS) ./src/Main.cpp ./src/Parse.cpp ./src/Expansion.cpp ./src/Analyze.cpp ./src/Command.cpp ./src/RShell.cpp -o rshell
