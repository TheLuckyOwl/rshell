#ifndef RSHELL_H
#define RSHELL_H

#include <iostream>
#include <string>
#include "TempParse.h"
//#include "Expansion.h"
//#include "Analyze.h"
//#include "Command.h"

using namespace std;

class RShell {
  private:
    string commandLine;
    int exitStatus;
    Parse parser;

    void parseString();
  public:
    void inputLoop();
    void outputString(string givenString);
    void setExit();
    string readCommandLine();
};

#endif
