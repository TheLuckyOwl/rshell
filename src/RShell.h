#ifndef RSHELL_H
#define RSHELL_H

#include <iostream>
#include <string>
#include "Parse.h"

using namespace std;

//RShell Class, will be used to take input from the terminal.

class RShell {
  private:
    string commandLine;
    int exitStatus;
    Parse parser;

    void parseString();
  public:
    void inputLoop();
    void outputString( string givenString );
    void setExit();
    string readCommandLine();
};

#endif
