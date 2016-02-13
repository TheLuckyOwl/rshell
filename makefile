COMPILE = g++
WFLAGS = -Wall -Werror -ansi -pedantic
SHELL := /bin/bash

SOURCEDIR = ./src/
BINDIR = ./bin/


all: rshell

rshell:
	mkdir -p $(BINDIR)
	g++ $(WFLAGS) $(SOURCEDIR)Main.cpp $(SOURCEDIR)Parse.cpp $(SOURCEDIR)Expansion.cpp $(SOURCEDIR)Analyze.cpp $(SOURCEDIR)Command.cpp $(SOURCEDIR)RShell.cpp -o $(BINDIR)rshell
