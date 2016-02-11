#ifndef COMMAND_H
#define COMMAND_H

#include <string>

using namespace std;

class Command {
  private:
    string commandString;
	string argumentString;

	int forkFunction(char** commandArray);
  public:
    int callCommand(string givenCommand, string givenArgument); 
};
#endif
