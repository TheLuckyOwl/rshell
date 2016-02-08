#ifndef COMMAND_H
#define COMMAND_H

#include "RShell.h"
#include <string>

using namespace std;

class Command {
  private:
    string commandString;
	string argumentString;
    //RShell* rshell;
  public:
    //void callCommand(string givenCommand, string givenArgument); 
    //void setRShell(RShell* givenRShell);
};
#endif
